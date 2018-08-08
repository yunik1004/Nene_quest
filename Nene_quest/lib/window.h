#ifndef _WINDOW_H
#define _WINDOW_H

#include <gl/glew.h>
#include <GLFW/glfw3.h>
#include "../scene/scene.h"

#define DEFAULT_WINDOW_WIDTH 960	// (1920 / 2)
#define DEFAULT_WINDOW_HEIGHT 540	// (1080 / 2)

class Window {
private:
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
	void setWindowPos(int, int);
	void setWindowPos_middle(void);
};

Window *getMainWindow(void);
void setMainWindow(Window *);

#endif // !_WINDOW_H
