#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>

class ModelOBJ {
private:
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;
	GLuint rendering_program;
	GLuint VAO, VBO, UVBO;
	GLuint texture;
	GLuint textureID;
	bool isLoadSuccess;
	static bool loadOBJ(const char *, std::vector<glm::vec3> &, std::vector<glm::vec2> &, std::vector<glm::vec3> &);
public:
	ModelOBJ(const char *, const char *);
	~ModelOBJ(void);
	void ModelOBJ::setMVP(const GLfloat *);
	void render(glm::vec3, GLfloat);
};
