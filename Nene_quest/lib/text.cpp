#include "text.h"
#include <glm/gtc/type_ptr.hpp>
#include "shader.h"
#include "../resource.h"

using namespace std;

static GLuint text_compile_shaders(void) {
	const GLchar *vertex_shader_src =
#include "text.vert"
;
	const GLchar *fragment_shader_src =
#include "text.frag"
;

	return VF_compile_shader(vertex_shader_src, fragment_shader_src);
}

Text::Text(char *fontPath) {
	isLoadSuccess = false;

	if (FT_Init_FreeType(&ft)) {
		cerr << "Error: Could not init FreeType Library" << endl;
		return;
	}
	/* Load font as face */
	if (FT_New_Face(ft, fontPath, 0, &face)) {
		cerr << "Error: Failed to load font" << endl;
		return;
	}

	/* Set size to load glyphs */
	FT_Set_Pixel_Sizes(face, 0, 96);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	rendering_program = text_compile_shaders();

	/* Configure VAO */
	glGenVertexArrays(1, &VAO);

	/* Configure VBO for texture quads */
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);	/* quad */

	isLoadSuccess = true;
}

Text::~Text(void) {
	bool fast_return = false;

	if (face) {
		FT_Done_Face(face);
	}
	else {
		fast_return = true;
	}

	if (ft) {
		FT_Done_FreeType(ft);
	}
	else {
		fast_return = true;
	}

	if (fast_return) {
		return;
	}

	for (auto const& c : characters) {
		glDeleteTextures(1, &c.second.textureID);
	}

	characters.clear();

	glDeleteBuffers(1, &VBO);
	glDeleteVertexArrays(1, &VAO);
	glDeleteProgram(rendering_program);
}

void Text::setMVP(const GLfloat *value) {
	if (!isLoadSuccess) {
		return;
	}

	GLuint MatrixID = glGetUniformLocation(rendering_program, "MVP");
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, value);
}

void Text::renderText(char *text, glm::vec2 coord, FT_UInt size, glm::vec3 color) {
	if (!isLoadSuccess) {
		return;
	}

	FT_Set_Pixel_Sizes(face, 0, size);

	GLfloat x = coord.x;
	GLfloat y = coord.y;

	/* Bind VAO */
	glBindVertexArray(VAO);

	/* Use shader */
	glUseProgram(rendering_program);

	glUniform3fv(glGetUniformLocation(rendering_program, "textColor"), 1, glm::value_ptr(color));

	glActiveTexture(GL_TEXTURE0);

	/* 1st attribute buffer : vertices */
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (void *)0);

	const char *p;
	for (p = text; *p; p++) {
		Character ch;
		try {
			ch = loadChar(*p, size);
		}
		catch (exception& e){
			cerr << e.what() << endl;
			continue;
		}

		GLfloat xpos = x + ch.bearing.x;
		GLfloat ypos = y - (ch.size.y - ch.bearing.y);

		GLfloat w = (GLfloat) ch.size.x;
		GLfloat h = (GLfloat) ch.size.y;

		/* Update VBO for each character */
		GLfloat vertices[6][4] = {
			{xpos, ypos + h, 0.0, 0.0},
			{xpos, ypos, 0.0, 1.0},
			{xpos + w, ypos, 1.0, 1.0},
			{xpos, ypos + h, 0.0, 0.0},
			{xpos + w, ypos, 1.0, 1.0},
			{xpos + w, ypos + h, 1.0, 0.0}
		};

		/* Render glyph texture over quad */
		glBindTexture(GL_TEXTURE_2D, ch.textureID);

		/* Update content of VBO memory */
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

		/* Render quad */
		glDrawArrays(GL_TRIANGLES, 0, 6);

		/* Advance cursors for next glyph (advance := # of 1/64 pixels) */
		x += ch.advance / 64;
	}

	glDisableVertexAttribArray(0);
}

Character Text::loadChar(FT_ULong c, FT_UInt size) {
	/* If character already exists, then return */
	map<pair<FT_ULong, FT_UInt>, Character>::iterator itr;
	if ((itr = characters.find(std::make_pair(c, size))) != characters.end()) {
		return itr->second;
	}

	/* Load character glyph */
	if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
		throw "Error: Fail to load Glyph";
	}

	/* Generate texture */
	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(
		GL_TEXTURE_2D,
		0,
		GL_RED,
		face->glyph->bitmap.width,
		face->glyph->bitmap.rows,
		0,
		GL_RED,
		GL_UNSIGNED_BYTE,
		face->glyph->bitmap.buffer
	);

	/* Set texture options */
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	/* Load character */
	Character character = {
		texture,
		glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
		glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
		(GLfloat) face->glyph->advance.x
	};

	characters.insert(pair<pair<FT_ULong, FT_UInt>, Character>(make_pair(c, size), character));
	
	return character;
}
