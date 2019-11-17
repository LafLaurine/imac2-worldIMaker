#version 330 core

in vec2 vTexCoords;
uniform sampler2D uTexture;
uniform sampler2D uCloudTexture;

out vec3 fFragTex;

void main() {
    vec3 tex1 = texture(uTexture, vTexCoords).xyz;
    vec3 tex2 = texture(uCloudTexture, vTexCoords).xyz;
    fFragTex = tex1 + tex2;
}
