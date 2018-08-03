#pragma once

#include <iostream>
#include <map>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <ft2build.h>
#include FT_FREETYPE_H

struct Character {
	GLuint textureID;	/* ID handle of the glyph texture */
	glm::ivec2 size;	/* Size of glyph */
	glm::ivec2 bearing;	/* Offset from baseline to left/top of glyph */
	GLfloat advance;		/* Horizontal offset to advance to next glyph */
};

class Text {
private:
	FT_Library ft;
	FT_Face face;
	GLuint rendering_program;
	GLuint VAO, VBO;
	std::map<FT_ULong, Character> characters;
	bool isLoadSuccess;
	Character loadChar(FT_ULong);
public:
	Text(char *);
	~Text(void);
	void setPixelHeight(FT_UInt);
	void setMVP(const GLfloat *);
	void renderText(char *, GLfloat, GLfloat, GLfloat, glm::vec3);
};
