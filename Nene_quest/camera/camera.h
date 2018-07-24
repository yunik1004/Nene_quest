#pragma once

#include <glm/glm.hpp>

class Camera {
public:
	glm::mat4 projection;
	glm::mat4 view;
	Camera();
	glm::mat4 mvp(glm::mat4 model);
};