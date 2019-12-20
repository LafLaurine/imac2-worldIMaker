#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout(location = 2) in vec3 aVertexColor;

uniform mat4 uModel;
uniform mat4 uViewProj;

out vec3 vNormal;
out vec3 vPos;
out vec3 vFragColor;

void main() {
	vNormal = aNormal;
    vFragColor = aVertexColor;
    vPos = vec3(uModel * vec4(aPos, 1.0));
    gl_Position = uViewProj * uModel * vec4(aPos, 1.0);
}