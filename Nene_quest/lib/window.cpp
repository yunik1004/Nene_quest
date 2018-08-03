#include "window.h"
#include <iostream>
#include <cmath>
#include "../scene/mainScene/mainScene.h"

using namespace std;

Window::Window(char* name) {
	/* Window size, name */
	window = glfwCreateWindow(DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT, name, NULL, NULL);
	if (!window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	/* Anti-aliasing */
	glfwWindowHint(GLFW_SAMPLES, 4);

	/* Resizability */
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
	glfwSetWindowAspectRatio(window, DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT);

	glfwMakeContextCurrent(window);
	glClearColor(0, 0, 0, 1);

	/* FPS limit: 60 */
	glfwSwapInterval(1);

	/* Size callback */
	glfwSetWindowSizeCallback(window, &Window::windowSizeCallback);

	/* Initialize glew */
	GLenum errorCode = glewInit();
	if (errorCode != GLEW_OK) {
		cerr << "Error: Fail to initialize GLEW - " << glewGetErrorString(errorCode) << endl;
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	if (!GLEW_VERSION_4_3) {
		cerr << "OpenGL 4.3 API is not avaliable." << endl;
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	// Set OpenGL options
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

Window::~Window(void) {
	if (scene != NULL) {
		delete scene;
	}
	glfwTerminate();
}

void Window::scene_update(void) {
	Scene *scene_next = scene->update();
	if (scene_next != scene) {
		delete scene;
		scene = scene_next;
	}
}

void Window::setScene(Scene *newScene) {
	scene = newScene;
}

void Window::render(void) {
	GLint m_viewport[4];

	while (!glfwWindowShouldClose(window)) {
		glGetIntegerv(GL_VIEWPORT, m_viewport);
		glScissor(m_viewport[0], m_viewport[1], m_viewport[2], m_viewport[3]);
		glEnable(GL_SCISSOR_TEST);

		scene_update();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}

void Window::setKeyCallback(GLFWkeyfun cbfun) {
	glfwSetKeyCallback(window, cbfun);
}

void Window::windowSizeCallback(GLFWwindow *window, int w, int h) {
	GLfloat widthFactor = (GLfloat)w / (GLfloat)DEFAULT_WINDOW_WIDTH;
	GLfloat heightFactor = (GLfloat)h / (GLfloat)DEFAULT_WINDOW_HEIGHT;

	GLfloat sizeFactor = widthFactor < heightFactor ? widthFactor : heightFactor;

	GLint modifiedWidth =  ceil(DEFAULT_WINDOW_WIDTH * sizeFactor) + 1;
	GLint modifiedHeight = ceil(DEFAULT_WINDOW_HEIGHT * sizeFactor) + 1;

	glViewport(floor((w - modifiedWidth) / 2.0), floor((h - modifiedHeight) / 2.0), modifiedWidth, modifiedHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(-1.0 * sizeFactor, 1.0 * sizeFactor, -1.0 * sizeFactor, 1.0 * sizeFactor, 0.0, 1.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

Window *main_window;

Window *getMainWindow(void) {
	return main_window;
}

void setMainWindow(Window *window) {
	if (main_window != NULL) {
		cerr << "Error: Main window is not empty" << endl;
	}

	main_window = window;
}
