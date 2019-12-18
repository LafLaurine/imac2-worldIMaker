#version 330 core

in vec3 vNormal;


uniform mat4 uNormalMat;

void main() {
	vec3 normal = (uNormalMat * vec4(vNormal, 0.)).xyz;
    fragColor = vec4(normal, 1.0f);
}