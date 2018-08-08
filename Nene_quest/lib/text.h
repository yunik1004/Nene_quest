#ifndef _TEXT_H
#define _TEXT_H

#include <iostream>
#include <map>
#include <GL/glew.h>
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
	std::map<std::pair<FT_ULong, FT_UInt>, Character> characters;
	bool isLoadSuccess;
	Character loadChar(FT_ULong, FT_UInt);
public:
	Text(char *);
	~Text(void);
	void setMVP(const GLfloat *);
	void renderText(char *, glm::vec2, FT_UInt, glm::vec3);
};

#endif // !_TEXT_H
