#include "window.h"
#include <iostream>
#include "../scene/mainScene/mainScene.h"

static Scene *scene_next;

using namespace std;

Window::Window(char* name) {
	glfwSetErrorCallback(&Window::errorCallback);

	/* Initialize glfw */
	if (!glfwInit()) {
		cerr << "Error: Fail to initialize GLFW" << endl;
		exit(EXIT_FAILURE);
	}

	/* OpenGL version : 3.3 */
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

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
	//glfwSetWindowAspectRatio(window, DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT);

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

	if (!GLEW_VERSION_3_3) {
		cerr << "OpenGL 3.3 API is not avaliable." << endl;
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	scene = new mainScene(window);
}

Window::~Window(void) {
	delete scene;
	glfwTerminate();
}

void Window::scene_update(void) {
	scene_next = scene->update();
	if (scene_next != scene) {
		delete scene;
		scene = scene_next;
	}
}

void Window::render(void) {
	while (!glfwWindowShouldClose(window)) {
		scene_update();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}

void Window::errorCallback(int errorCode, const char *errorDescription) {
	fprintf(stderr, "Error: %s\n", errorDescription);
}

void Window::windowSizeCallback(GLFWwindow *window, int w, int h) {
	GLfloat widthFactor = (GLfloat)w / (GLfloat)DEFAULT_WINDOW_WIDTH;
	GLfloat heightFactor = (GLfloat)h / (GLfloat)DEFAULT_WINDOW_HEIGHT;

	GLfloat sizeFactor = widthFactor < heightFactor ? widthFactor : heightFactor;

	GLfloat modifiedWidth = DEFAULT_WINDOW_WIDTH * sizeFactor;
	GLfloat modifiedHeight = DEFAULT_WINDOW_HEIGHT * sizeFactor;

	glViewport((int)(((float)w - modifiedWidth) / 2.0), (int)(((float)h - modifiedHeight) / 2.0), (int)modifiedWidth, (int)modifiedHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(-1.0 * sizeFactor, 1.0 * sizeFactor, -1.0 * sizeFactor, 1.0 * sizeFactor, 0.0, 1.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
