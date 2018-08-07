R"(
#version 430 core

//in vec2 UV;
out vec3 color;

//uniform sampler2D textureSampler;

void main (void) {
	//color = texture(textureSampler, UV).rgb;
	color = vec3(0.5, 0.5, 0.5);
}
)"