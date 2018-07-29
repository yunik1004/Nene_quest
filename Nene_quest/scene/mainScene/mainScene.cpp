#include "mainScene.h"
#include <glm/glm.hpp>

static GLuint mainScene_compile_shaders(void) {
	const GLchar *vertex_shader_src =
#include "shader.vert"
;
	const GLchar *fragment_shader_src =
#include "shader.frag"
;
	
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

mainScene::mainScene(GLFWwindow *window) {
	camera = Camera();
	rendering_program = mainScene_compile_shaders();
	glGenVertexArrays(1, &vertex_array_object);
	glBindVertexArray(vertex_array_object);
	this->window = window;

	// Triangle vertex
	static const GLfloat g_vertex_buffer_data[] = {
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
	};
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
}

mainScene::~mainScene(void) {
	glDeleteVertexArrays(1, &vertex_array_object);
	glDeleteProgram(rendering_program);
}

Scene *mainScene::update(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(rendering_program);

	glm::mat4 mvp = camera.mvp(glm::mat4(1.0f));
	GLuint MatrixID = glGetUniformLocation(rendering_program, "MVP");
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glDisableVertexAttribArray(0);

	return this;
}
