#include "camera.h"
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera() {
	projection = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 100.0f);
	view = glm::lookAt(
		glm::vec3(4, 3, 3),
		glm::vec3(0, 0, 0),
		glm::vec3(0, 1, 0)
	);
}

glm::mat4 Camera::mvp(glm::mat4 model) {
	return this->projection * this->view * model;
}
