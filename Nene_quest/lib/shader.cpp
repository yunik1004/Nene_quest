#include "shader.h"
#include <iostream>

GLuint compile_shader(const GLchar *shaderSrc, const GLenum shaderType) {
	GLuint shader = glCreateShader(shaderType);

	glShaderSource(shader, 1, &shaderSrc, NULL);
	glCompileShader(shader);

	return shader;
}
