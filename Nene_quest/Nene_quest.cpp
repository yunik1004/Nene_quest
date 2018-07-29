// Nene_quest.cpp : Defines the entry point for the application.
//

#include "scene/mainScene/mainScene.h"
#include "window/window.h"

int main(int argc, char *argv[]) {
	Window *main_window = new Window("Nene Quest");
	setMainWindow(main_window);

	main_window->setScene(new mainScene());
	main_window->render();

	delete main_window;
	return 0;
}
