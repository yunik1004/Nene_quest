#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../scene.h"
#include "../../camera/camera.h"

class mainScene : public Scene {
private:
	GLuint vertexbuffer;
	static void keyCallback(GLFWwindow *, int, int, int, int);
public:
	mainScene(void);
	~mainScene(void);
	Camera camera;
	Scene* update(void);
};
