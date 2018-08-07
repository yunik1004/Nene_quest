R"(
#version 430 core

layout (location = 0) in vec3 vertex;
//layout (location = 1) in vec2 vertexUV;

//out vec2 UV;

uniform mat4 MVP;

void main (void) {
	gl_Position = MVP * vec4(vertex, 1.0);
	//UV = vertexUV;
}
)"