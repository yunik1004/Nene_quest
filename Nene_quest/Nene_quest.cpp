// Nene_quest.cpp : Defines the entry point for the application.
//

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "window/window.h"

static void keyCallback(GLFWwindow *, int, int, int, int);

int main(int argc, char *argv[]) {
	Window *curr_window = new Window("Nene Quest");

	glfwSetKeyCallback(curr_window->window, keyCallback);

	curr_window->render();

	delete curr_window;
	return 0;
}

static void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
	switch (key)
	{
	case GLFW_KEY_ESCAPE:
		if (action == GLFW_PRESS) {
			glfwSetWindowShouldClose(window, GLFW_TRUE);
		}
		break;
	default:
		break;
	}
}
