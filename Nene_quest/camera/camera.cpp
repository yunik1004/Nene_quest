#include "camera.h"
#include <glm/gtc/matrix_transform.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/transform.hpp>
#include "../lib/window.h"

Camera::Camera(void) {
	projection = glm::ortho(0.0f, (float)DEFAULT_WINDOW_WIDTH, 0.0f, (float)DEFAULT_WINDOW_HEIGHT);

	view = glm::lookAt(
		glm::vec3(0, 0, 1),
		glm::vec3(0, 0, 0),
		glm::vec3(0, 1, 0)
	);
}

glm::mat4 Camera::mvp(glm::mat4 model) {
	return projection * view * model;
}

glm::mat4  Camera::mvp(void) {
	return projection * view;
}

glm::mat4 Camera::mp(glm::mat4 model) {
	return projection * model;
}
glm::mat4 Camera::mp(void) {
	return projection;
}
