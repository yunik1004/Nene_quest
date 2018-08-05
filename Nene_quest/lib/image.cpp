#include "image.h"
#include <cstdio>
#include <iostream>
#include <png.h>

using namespace std;

ImagePNG::ImagePNG(const char *filename) {
	if (!loadPNG(filename)) {
		cerr << "Error: Fail to load png file" << endl;
		return;
	}
}

ImagePNG::~ImagePNG(void) {
	if (data) {
		free(data);
	}
}

bool ImagePNG::loadPNG(const char *filename) {
	unsigned int sig_read = 0;

	FILE *fp;
	fopen_s(&fp, filename, "rb");
	if (!fp) {
		cerr << "Error: Can't find png file" << endl;
		return false;
	}

	/* Create and initialize png_struct */
	png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if (!png_ptr) {
		cerr << "Error: Can't create png read_struct" << endl;
		fclose(fp);
		return false;
	}

	/* Allocate and initialize the memory for image information */
	png_infop info_ptr = png_create_info_struct(png_ptr);
	if (!info_ptr) {
		cerr << "Error: Can't create png info_struct" << endl;
		png_destroy_read_struct(&png_ptr, NULL, NULL);
		fclose(fp);
		return false;
	}

	/* Set error handling */
	if (setjmp(png_jmpbuf(png_ptr))) {
		png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
		fclose(fp);
		return false;
	}

	/* Set up the output control */
	png_init_io(png_ptr, fp);

	/* If we have already read some of the signature */
	png_set_sig_bytes(png_ptr, sig_read);

	png_read_png(png_ptr, info_ptr, PNG_TRANSFORM_STRIP_16 | PNG_TRANSFORM_PACKING | PNG_TRANSFORM_EXPAND, NULL);

	int bit_depth, color_type, interlace_type;
	png_get_IHDR(png_ptr, info_ptr, &width, &height, &bit_depth, &color_type, &interlace_type, NULL, NULL);
	hasAlpha = color_type & PNG_COLOR_MASK_ALPHA;

	unsigned int row_bytes = (unsigned int) png_get_rowbytes(png_ptr, info_ptr);
	data = (unsigned char *) malloc(row_bytes * height);

	png_bytepp row_pointers = png_get_rows(png_ptr, info_ptr);

	/* png is ordered top to bottom, but OpenGL expect it bottom to top. So, order should be swapped */
	for (unsigned int i = 0; i < height; i++) {
		memcpy(data + (row_bytes * (height -1 - i)), row_pointers[i], row_bytes);
	}

	/* Clean up and free memory */
	png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
	fclose(fp);
	return true;
}

GLuint loadTexturePNG(const char *filename) {
	ImagePNG *png = new ImagePNG(filename);

	GLuint textureID;
	glGenTextures(1, &textureID);

	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(
		GL_TEXTURE_2D,
		0,
		png->hasAlpha ? 4 : 3,
		png->width,
		png->height,
		0,
		png->hasAlpha ? GL_RGBA : GL_RGB,
		GL_UNSIGNED_BYTE,
		png->data
	);

	delete png;

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glGenerateMipmap(GL_TEXTURE_2D);

	return textureID;
}
