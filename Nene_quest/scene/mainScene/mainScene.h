#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../scene.h"
#include "../../camera/camera.h"
#include "../../lib/audio.h"
#include "../../lib/text.h"

class mainScene : public Scene {
private:
	Audio *audio;
	Text *text;
	static void keyCallback(GLFWwindow *, int, int, int, int);
public:
	mainScene(void);
	~mainScene(void);
	Camera camera;
	Scene* update(void);
};
