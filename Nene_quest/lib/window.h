#pragma once

#include <gl/glew.h>
#include <GLFW/glfw3.h>
#include "../scene/scene.h"

#define DEFAULT_WINDOW_WIDTH (1920 / 2)
#define DEFAULT_WINDOW_HEIGHT (1080 / 2)

class Window {
private:
	static void errorCallback(int, const char *);
	static void windowSizeCallback(GLFWwindow *, int, int);
	void scene_update(void);
public:
	Window(char *);
	~Window(void);
	GLFWwindow *window;
	Scene *scene;
	void setScene(Scene *);
	void render(void);
	void setKeyCallback(GLFWkeyfun);
};

Window *getMainWindow(void);
void setMainWindow(Window *);
