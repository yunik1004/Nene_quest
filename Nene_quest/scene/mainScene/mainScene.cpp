#include "mainScene.h"
#include <algorithm>
#include <glm/glm.hpp>
#include "../../lib/window.h"
#include "../../resource.h"
#include "../../keysetting.h"
#include "../playScene/playScene.h"

enum KEY_STATE {
	STATE_IDLE,
	STATE_UP,
	STATE_DOWN
};

enum CURSOR_STATE {
	CURSOR_1P = 0,
	CURSOR_2P = 1,
	CURSOR_EXIT = 2
};

enum NEXT_SCENE {
	CURRENT_SCENE,
	PLAY_SCENE
};

static KEY_STATE key_state;
static CURSOR_STATE cursor_state;
static NEXT_SCENE next_scene;

using namespace std;

mainScene::mainScene(void) {
	/* Create scene */
	Window *main_window = getMainWindow();
	main_window->setKeyCallback(&mainScene::keyCallback);

	/* Camera */
	camera = Camera();

	/* Title */
	title = new ModelOBJ(TITLE_OBJ, TITLE_UV);

	/* Text */
	text = new Text(NEW_GAME_FONT);

	/* Background color - white */
	glClearColor(1.0, 1.0, 1.0, 0.0);

	/* State */
	key_state = STATE_IDLE;
	cursor_state = CURSOR_1P;
	next_scene = CURRENT_SCENE;
}

mainScene::~mainScene(void) {
	delete title;
	delete text;
}

void mainScene::keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
	switch (key)
	{
	case KEY_EXIT:
		if (action == GLFW_PRESS) {
			glfwSetWindowShouldClose(window, GLFW_TRUE);
		}
		break;
	case KEY_UP:
		if (action == GLFW_PRESS) {
			key_state = STATE_UP;
		}
		else if (action == GLFW_RELEASE) {
			key_state = STATE_IDLE;
		}
		break;
	case KEY_DOWN:
		if (action == GLFW_PRESS) {
			key_state = STATE_DOWN;
		}
		else if (action == GLFW_RELEASE) {
			key_state = STATE_IDLE;
		}
		break;
	case KEY_SELECT:
		switch (cursor_state)
		{
		case CURSOR_1P:
			next_scene = PLAY_SCENE;
			break;
		case CURSOR_2P:
			// Should be implemented
			break;
		case CURSOR_EXIT:
			glfwSetWindowShouldClose(window, GLFW_TRUE);
			break;
		}
		break;
	default:
		break;
	}
}

Scene *mainScene::update(void) {
	switch (next_scene)
	{
	case PLAY_SCENE:
	{
		playScene *pScene = new playScene();
		return pScene;
	}
	default:
		break;
	}

	switch (key_state)
	{
	case STATE_IDLE:
		break;
	case STATE_UP:
		cursor_state = static_cast<CURSOR_STATE> (max(cursor_state - 1, (int)CURSOR_1P));
		break;
	case STATE_DOWN:
		cursor_state = static_cast<CURSOR_STATE> (min(cursor_state + 1, (int)CURSOR_EXIT));
		break;
	default:
		break;
	}

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::mat4 mvp = camera.mp();

	/* Title */
	title->setMVP(&mvp[0][0]);
	title->render(glm::vec3(0.0f, 0.0f, 0.0f), 1.0f);

	/* Text */
	text->setMVP(&mvp[0][0]);
	text->renderText("1 Player Game", glm::vec2(390.0f, 130.0f), 1.0f, glm::vec3(0.3f, 0.3f, 0.3f));
	text->renderText("2 Player Game", glm::vec2(390.0f, 80.0f), 1.0f, glm::vec3(0.3f, 0.3f, 0.3f));
	text->renderText("E       x       i       t", glm::vec2(390.0f, 30.0f), 1.0f, glm::vec3(0.3f, 0.3f, 0.3f));

	/* Cursor */
	// To be implemented

	return this;
}
