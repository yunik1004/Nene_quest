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
}

ModelOBJ::~ModelOBJ(void) {

}

void ModelOBJ::setMVP(const GLfloat *value) {

}

void ModelOBJ::render(void) {

}
