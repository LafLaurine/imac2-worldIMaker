#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aVertexTexCoords; // Texture

uniform mat4 uModelView;
uniform mat4 uNormalMat;
uniform mat4 uViewProj;

out vec3 vNormal;
out vec3 vPos;
out vec2 vTexCoords;

void main() {
	vNormal = vec3(uNormalMat * vec4(aNormal,0.0));
    vTexCoords = -aVertexTexCoords;
    vPos = vec3(uModelView * vec4(aPos, 1.0));
    gl_Position = uViewProj * uModelView * vec4(aPos, 1.0);
}