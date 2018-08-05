#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../scene.h"
#include "../../camera/camera.h"
#include "../../lib/audio.h"

class playScene : public Scene {
private:
	Audio *audio;
	Camera camera;
	static void keyCallback(GLFWwindow *, int, int, int, int);
public:
	playScene(void);
	~playScene(void);
	Scene* update(void);
};
