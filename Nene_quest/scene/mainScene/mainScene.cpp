#include "mainScene.h"
#include <glm/glm.hpp>
#include "../../lib/window.h"
#include "../../resource.h"

using namespace std;

mainScene::mainScene(void) {
	/* Create scene */
	Window *main_window = getMainWindow();
	main_window->setKeyCallback(&mainScene::keyCallback);

	/* Audio */
	audio = new Audio(TEST_WAV);
	audio->play();
	audio->setLoop(true);

	/* Camera */
	camera = Camera();

	/* Text */
	text = new Text(NEW_GAME_FONT);

	/* Background color - white */
	glClearColor(1.0, 1.0, 1.0, 0.0);
}

mainScene::~mainScene(void) {
	delete audio;
	delete text;
}

void mainScene::keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
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

Scene *mainScene::update(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::mat4 mvp = camera.mp();

	/* Text */
	text->setMVP(&mvp[0][0]);
	text->renderText("Hello", 25.0f, 25.0f, 1.0f, glm::vec3(0.5, 0.8f, 0.2f));

	return this;
}
