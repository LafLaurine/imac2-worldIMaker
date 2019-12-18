#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;


uniform mat4 uModel;
uniform mat4 uViewProj;

out vec3 vNormal;

void main() {
	vNormal = aNormal;
    gl_Position = uViewProj * uModel * vec4(aPos, 1.0);
}