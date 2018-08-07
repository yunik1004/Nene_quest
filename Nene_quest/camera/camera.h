#ifndef _CAMERA_H
#define _CAMERA_H

#include <glm/glm.hpp>

class Camera {
public:
	Camera(void);
	glm::mat4 projection;
	glm::mat4 view;
	glm::mat4 mvp(glm::mat4);
	glm::mat4 mvp(void);
	glm::mat4 mp(glm::mat4);
	glm::mat4 mp(void);
};

#endif // !_CAMERA_H
