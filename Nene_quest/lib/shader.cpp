#include "shader.h"
#include <iostream>

GLuint compile_shader(const GLchar *shaderSrc, const GLenum shaderType) {
	GLuint shader = glCreateShader(shaderType);

	glShaderSource(shader, 1, &shaderSrc, NULL);
	glCompileShader(shader);

	return shader;
}

GLuint VF_compile_shader(const GLchar *vertex_shader_src, const GLchar *fragment_shader_src) {
	GLuint vertex_shader = compile_shader(vertex_shader_src, GL_VERTEX_SHADER);
	GLuint fragment_shader = compile_shader(fragment_shader_src, GL_FRAGMENT_SHADER);
	GLuint program = glCreateProgram();

	glAttachShader(program, vertex_shader);
	glAttachShader(program, fragment_shader);
	glLinkProgram(program);

	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);

	return program;
}
