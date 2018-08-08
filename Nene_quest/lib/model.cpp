#include "model.h"
#define TINYOBJLOADER_IMPLEMENTATION
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
	std::string err;

	bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &err, objFilename);
	if (!err.empty()) {
		cerr << err << endl;
		return;
	}
	if (!ret) {
		cerr << "Fail to load obj file" << endl;
		return;
	}

	printf("# of vertices  = %d\n", (int)(attrib.vertices.size()) / 3);
	printf("# of normals   = %d\n", (int)(attrib.normals.size()) / 3);
	printf("# of texcoords = %d\n", (int)(attrib.texcoords.size()) / 2);
	printf("# of materials = %d\n", (int)materials.size());
	printf("# of shapes    = %d\n", (int)shapes.size());
}

ModelOBJ::~ModelOBJ(void) {

}

void ModelOBJ::setMVP(const GLfloat *value) {

}

void ModelOBJ::render(void) {

}
