#ifndef _IMAGE_H
#define _IMAGE_H

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

#endif // !_IMAGE_H
