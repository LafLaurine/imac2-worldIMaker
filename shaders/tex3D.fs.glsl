#version 330 core

in vec2 vTexCoords;
uniform sampler2D uTexture;

out vec3 fFragTex;

void main() {
    fFragTex = texture(uTexture, vTexCoords).xyz;
}
