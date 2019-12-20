#version 330 core
out vec4 fragColor;

in vec3 vPos;
in vec3 vNormal;

uniform vec3 lightPos;
uniform mat4 uNormalMat;

void main() {
    float lum = max(-dot(lightPos, vNormal), 0.8);
    vec3 normal = (uNormalMat * vec4(vNormal, 0.)).xyz;
    fragColor = vec4(lum * normal , 1.0f);
}
