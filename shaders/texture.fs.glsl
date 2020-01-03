#version 330

in vec2 vTexCoord;

out vec4 fFragColor;

uniform sampler2D uTexture;

void main() {
	vec4 texColor = texture(uTexture, vTexCoord);
    fFragColor = texColor;
}