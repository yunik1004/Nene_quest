#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../lib/shader.h"

class Scene {
public:
	virtual ~Scene(void) {}
	virtual Scene* update(void) = 0;
};
