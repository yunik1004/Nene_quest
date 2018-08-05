#include "model.h"
#include <cstdio>
#include <iostream>
#include "shader.h"
#include "image.h"

#define OBJ_HEADER_SIZE 1023

using namespace std;

static GLuint model_compile_shaders(void) {
	const GLchar *vertex_shader_src =
#include "model.vert"
;
	const GLchar *fragment_shader_src =
#include "model.frag"
;

	return VF_compile_shader(vertex_shader_src, fragment_shader_src);
}

ModelOBJ::ModelOBJ(const char *objFilename, const char *uvFilename) {
	isLoadSuccess = false;
	if (!loadOBJ(objFilename, vertices, uvs, normals)) {
		cerr << "Error: Fail to load obj file" << endl;
		return;
	}

	texture = loadTexturePNG(uvFilename);

	rendering_program = model_compile_shaders();
	textureID = glGetUniformLocation(rendering_program, "textureSampler");

	/* Configure VAO */
	glGenVertexArrays(1, &VAO);

	/* Configure VBO */
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

	/* Configure UVBO */
	glGenBuffers(1, &UVBO);
	glBindBuffer(GL_ARRAY_BUFFER, UVBO);
	glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);

	isLoadSuccess = true;
}

ModelOBJ::~ModelOBJ(void) {
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &UVBO);
	glDeleteVertexArrays(1, &VAO);
	glDeleteProgram(rendering_program);
	glDeleteTextures(1, &texture);

	vertices.clear();
	uvs.clear();
	normals.clear();
}

bool ModelOBJ::loadOBJ(const char *filename, vector<glm::vec3> &out_vertices, vector<glm::vec2> &out_uvs, vector<glm::vec3> &out_normals) {
	FILE *fp;
	fopen_s(&fp, filename, "r");
	if (!fp) {
		cerr << "Error: Can't find obj file" << endl;
		return false;
	}

	vector<unsigned int> vertexIndices, uvIndices, normalIndices;
	vector<glm::vec3> tmp_vertices;
	vector<glm::vec2> tmp_uvs;
	vector<glm::vec3> tmp_normals;

	char lineHeader[OBJ_HEADER_SIZE + 1];

	while (true) {
		if (fscanf_s(fp, "%s", lineHeader, OBJ_HEADER_SIZE) == EOF) {
			break;
		}

		if (strcmp(lineHeader, "v") == 0) {
			glm::vec3 vertex;
			fscanf_s(fp, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			tmp_vertices.push_back(vertex);
		}
		else if (strcmp(lineHeader, "vt") == 0) {
			glm::vec2 uv;
			fscanf_s(fp, "%f %f\n", &uv.x, &uv.y);
			tmp_uvs.push_back(uv);
		}
		else if (strcmp(lineHeader, "vn") == 0) {
			glm::vec3 normal;
			fscanf_s(fp, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			tmp_normals.push_back(normal);
		}
		else if (strcmp(lineHeader, "f") == 0) {
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			fscanf_s(fp, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
			for (int i = 0; i < 3; i++) {
				vertexIndices.push_back(vertexIndex[i]);
				uvIndices.push_back(uvIndex[i]);
				normalIndices.push_back(normalIndex[i]);
			}
		}
		else {
			/* Remove unnecessary line */
			fgets(lineHeader, OBJ_HEADER_SIZE, fp);
		}
	}

	for (unsigned int i = 0; i < vertexIndices.size(); i++) {
		glm::vec3 vertex = tmp_vertices[vertexIndices[i] - 1];
		glm::vec2 uv = tmp_uvs[uvIndices[i] - 1];
		glm::vec3 normal = tmp_normals[normalIndices[i] - 1];

		out_vertices.push_back(vertex);
		out_uvs.push_back(uv);
		out_normals.push_back(normal);
	}

	fclose(fp);
	return true;
}

void ModelOBJ::setMVP(const GLfloat *value) {
	if (!isLoadSuccess) {
		return;
	}

	GLuint MatrixID = glGetUniformLocation(rendering_program, "MVP");
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, value);
}

void ModelOBJ::render(glm::vec3 coord, GLfloat scale) {
	if (!isLoadSuccess) {
		return;
	}

	/* Bind VAO */
	glBindVertexArray(VAO);

	/* Use shader */
	glUseProgram(rendering_program);

	/* Bind our texture in Texture Unit 0 */
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	/* Set our texture sampler to use Texture Unit 0 */
	glUniform1i(textureID, 0);

	/* 1st attribute buffer : vertices */
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);

	/* 2nd attribute buffer : uvs */
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, UVBO);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void *)0);

	/* Draw triangles */
	glDrawArrays(GL_TRIANGLES, 0, (GLsizei)vertices.size());
	
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}
