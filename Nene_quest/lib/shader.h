#ifndef _SHADER_H
#define _SHADER_H

#include <GL/glew.h>

GLuint compile_shader(const GLchar *, const GLenum);
GLuint VF_compile_shader(const GLchar *, const GLchar *);

#endif // !_SHADER_H
