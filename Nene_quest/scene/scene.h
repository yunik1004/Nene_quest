#ifndef _SCENE_H
#define _SCENE_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../lib/shader.h"

class Scene {
public:
	virtual ~Scene(void) {}
	virtual Scene* update(void) = 0;
};

#endif // !_SCENE_H
