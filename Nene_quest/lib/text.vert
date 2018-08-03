R"(
#version 430 core

layout (location = 0) in vec4 vertex;
out vec2 TexCoords;

uniform mat4 MVP;

void main (void) {
	gl_Position = MVP * vec4(vertex.xy, 0.0, 1.0);
	TexCoords = vertex.zw;
}
)"