#ifndef _MAINSCENE_H
#define _MAINSCENE_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../scene.h"
#include "../../camera/camera.h"
#include "../../lib/text.h"
#include "../../lib/timer.h"

class mainScene : public Scene {
private:
	Text *title;
	Text *menu;
	Text *cursor;
	Timer timer;
	Camera camera;
	static void keyCallback(GLFWwindow *, int, int, int, int);
public:
	mainScene(void);
	~mainScene(void);
	Scene* update(void);
};

#endif // !_MAINSCENE_H
