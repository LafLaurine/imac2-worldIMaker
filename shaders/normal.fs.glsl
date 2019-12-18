#version 330 core
out vec4 fragColor;

in vec3 vNormal;
uniform mat4 uNormalMat;

void main() {
	vec3 normal = (uNormalMat * vec4(vNormal, 0.)).xyz;
    fragColor = vec4(normal, 1.0f);
}
