// Nene_quest.cpp : Defines the entry point for the application.
//

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "scene/scene.h"
#include "scene/mainScene/mainScene.h"

#define DEFAULT_WINDOW_WIDTH (1920 / 2)
#define DEFAULT_WINDOW_HEIGHT (1080 / 2)

static void errorCallback(int errorCode, const char* errorDescription);
static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
static void windowSizeCallback(GLFWwindow* window, int w, int h);
static void render(void);

Scene* scene;
Scene* scene_next;

using namespace std;

int main(int argc, char** argv) {
	glfwSetErrorCallback(errorCallback);

	if (!glfwInit()) {
		cerr << "Error: Fail to initialize GLFW" << endl;
		exit(EXIT_FAILURE);
	}

	/* OpenGL version : 3.3 */
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	/* Anti-aliasing */
	glfwWindowHint(GLFW_SAMPLES, 4);

	/* Window size, name */
	GLFWwindow* window = glfwCreateWindow(DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT, "Nene Quest", NULL, NULL);
	if (!window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	/* Resizability */
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
	//glfwSetWindowAspectRatio(window, DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT);

	glfwMakeContextCurrent(window);
	glClearColor(0, 0, 0, 1);

	/* FPS limit: 60 */
	glfwSwapInterval(1);

	glfwSetKeyCallback(window, keyCallback);
	glfwSetWindowSizeCallback(window, windowSizeCallback);

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

	while (!glfwWindowShouldClose(window)) {
		/* Rendering process. */
		render();

		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

static void errorCallback(int errorCode, const char* errorDescription) {
	fprintf(stderr, "Error: %s\n", errorDescription);
}

static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
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

static void windowSizeCallback(GLFWwindow* window, int w, int h) {
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

static void render(void) {
	scene_next = scene->update();
	if (scene_next != scene) {
		delete scene;
		scene = scene_next;
	}
}
