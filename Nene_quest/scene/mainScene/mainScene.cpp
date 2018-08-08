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
	title = new Text(TITLE_FONT);

	/* Text */
	menu = new Text(NEW_GAME_FONT);

	/* Cursor */
	cursor = new Text(NEW_GAME_FONT);

	/* Timer */
	timer = Timer();

	/* Background color - white */
	glClearColor(255 / 255.0, 253 / 255.0 , 252 / 255.0, 0.0);
	
	/* State */
	key_state = STATE_IDLE;
	cursor_state = CURSOR_1P;
	next_scene = CURRENT_SCENE;
}

mainScene::~mainScene(void) {
	if (title) {
		delete title;
	}
	if (menu) {
		delete menu;
	}
	if (cursor) {
		delete cursor;
	}
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
		timer.unsetTimer();
		break;
	case STATE_UP:
		if (timer.isFinish()) {
			timer.setTime(500);
			timer.startTimer();
			cursor_state = static_cast<CURSOR_STATE> (max(cursor_state - 1, (int)CURSOR_1P));
		}
		break;
	case STATE_DOWN:
		if (timer.isFinish()) {
			timer.setTime(500);
			timer.startTimer();
			cursor_state = static_cast<CURSOR_STATE> (min(cursor_state + 1, (int)CURSOR_EXIT));
		}
		break;
	}

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	
	glm::mat4 mvp_text = camera.mp();

	/* Title */
	title->setMVP(&mvp_text[0][0]);
	title->renderText("NENE QUEST", glm::vec2(230.0f, 330.0f), 96, glm::vec3(1.0f, 0.3f, 0.3f));

	/* Text */
	glm::vec2 player_1_loc = glm::vec2(350.0f, 130.0f);
	glm::vec2 player_2_loc = glm::vec2(350.0f, 80.0f);
	glm::vec2 exit_loc = glm::vec2(350.0f, 30.0f);

	glm::vec3 menu_color = glm::vec3(0.3f, 0.3f, 0.3f);

	menu->setMVP(&mvp_text[0][0]);
	menu->renderText("1 Player Game", player_1_loc, 48, menu_color);
	menu->renderText("2 Player Game", player_2_loc, 48, menu_color);
	menu->renderText("E      x      i      t", exit_loc, 48, menu_color);

	/* Cursor */
	glm::vec2 cursor_loc;
	switch (cursor_state)
	{
	case CURSOR_1P:
		cursor_loc = player_1_loc;
		break;
	case CURSOR_2P:
		cursor_loc = player_2_loc;
		break;
	case CURSOR_EXIT:
		cursor_loc = exit_loc;
		break;
	}
	cursor_loc -= glm::vec2(40.0f, 0.0f);

	cursor->setMVP(&mvp_text[0][0]);
	cursor->renderText(">", cursor_loc, 48, menu_color);

	return this;
}
