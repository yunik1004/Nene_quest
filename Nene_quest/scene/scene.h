#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../lib/shader.h"

class Scene {
protected:
	GLuint rendering_program;
	GLuint vertex_array_object;
	GLFWwindow* window;
public:
	virtual Scene* update(void) = 0;
};
