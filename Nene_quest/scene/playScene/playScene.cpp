#include "playScene.h"
#include "../mainScene/mainScene.h"
#include "../../lib/window.h"
#include "../../resource.h"
#include "../../keysetting.h"

enum NEXT_SCENE {
	CURRENT_SCENE,
	MAIN_SCENE,
	ENDING_SCENE
};

static NEXT_SCENE next_scene;

playScene::playScene(void) {
	/* Create scene */
	Window *main_window = getMainWindow();
	main_window->setKeyCallback(&playScene::keyCallback);

	/* Audio */
	audio = new Audio(TEST_WAV);
	audio->play();
	audio->setLoop(true);

	/* Camera */
	camera = Camera();

	/* Background color - black */
	glClearColor(0.0, 0.0, 0.0, 0.0);

	/* State */
	next_scene = CURRENT_SCENE;
}

playScene::~playScene(void) {
	delete audio;
}

void playScene::keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
	switch (key)
	{
	case KEY_EXIT:
		next_scene = MAIN_SCENE;
		break;
	case KEY_PAUSE:
		break;
	case KEY_UP:
		break;
	case KEY_DOWN:
		break;
	case KEY_LEFT:
		break;
	case KEY_RIGHT:
		break;
	case KEY_ATTACK:
		break;
	case KEY_JUMP:
		break;
	default:
		break;
	}
}

Scene *playScene::update(void) {
	switch (next_scene)
	{
	case MAIN_SCENE:
	{
		mainScene *mScene = new mainScene();
		return mScene;
	}
	default:
		break;
	}

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	return this;
}
