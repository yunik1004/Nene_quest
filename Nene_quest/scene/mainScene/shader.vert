R"(
#version 430 core

layout(location = 0) in vec3 vertexPosition_modelspace;

uniform mat4 MVP;

out vec4 vs_color;

void main (void) {
	gl_Position = MVP * vec4(vertexPosition_modelspace, 1);

	const vec4 colors[3] = vec4[3](vec4(1.0, 0.0, 0.0, 1.0),
								vec4(0.0, 1.0, 0.0, 1.0),
								vec4(0.0, 0.0, 1.0, 1.0));

	vs_color = colors[gl_VertexID];
}
)"