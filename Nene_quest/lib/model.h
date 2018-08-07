#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>
#include <tiny_obj_loader.h>

class ModelOBJ {
private:
	tinyobj::attrib_t attrib;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;
	GLuint rendering_program;
	GLuint VAO, VBO, UVBO;
	GLuint texture;
	GLuint textureID;
	bool isLoadSuccess;
public:
	ModelOBJ(const char *, const char *);
	~ModelOBJ(void);
	void ModelOBJ::setMVP(const GLfloat *);
	void render(void);
};
