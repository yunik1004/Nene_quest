// Nene_quest.cpp : Defines the entry point for the application.
//
#ifdef _MSC_VER
#ifndef _DEBUG
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif // !_DEBUG
#endif // !_MSC_VER

#include <gl/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "scene/mainScene/mainScene.h"
#include "lib/window.h"

static void errorCallback(int, const char *);

using namespace std;

int main(int argc, char *argv[]) {
	glfwSetErrorCallback(errorCallback);

	/* Initialize glfw */
	if (!glfwInit()) {
		cerr << "Error: Fail to initialize GLFW" << endl;
		exit(EXIT_FAILURE);
	}

	/* OpenGL version : 4.3 */
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	/* Create window */
	Window *main_window = new Window("Nene Quest");
	setMainWindow(main_window);
	main_window->setWindowPos_middle();

	main_window->setScene(new mainScene());
	main_window->render();

	delete main_window;

	glfwTerminate();
	return 0;
}

static void errorCallback(int errorCode, const char *errorDescription) {
	fprintf(stderr, "Error: %s\n", errorDescription);
}
