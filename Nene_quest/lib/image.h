#pragma once

#include <gl/glew.h>
#include <GLFW/glfw3.h>

class ImagePNG {
private:
	bool loadPNG(const char *);
public:
	ImagePNG(const char *);
	~ImagePNG(void);
	unsigned int width, height;
	bool hasAlpha;
	GLubyte *data;
};

GLuint loadTexturePNG(const char *);
