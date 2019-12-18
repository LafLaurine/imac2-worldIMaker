#version 330

layout(location = 0) in vec3 aVertexPosition; // Position
layout(location = 1) in vec3 aVertexNormal; // Normale
//layout(location = 2) in vec2 aVertexTexCoords; // Texture

//Matrices uniformes
uniform mat4 uMVMatrix;
uniform mat4 uMVPMatrix;
uniform mat4 uNormalMatrix;

out vec3 vPosition;
out vec3 vNormal;
//out vec2 vTexCoords;

void main() {
    //Passage en coordonées homogènes
    vec4 vertexPosition = vec4(aVertexPosition, 1);
    vec4 vertexNormal = vec4(aVertexNormal, 0);

    /* Position et normales */
    vPosition = vec3(uMVMatrix * vertexPosition);
    vNormal = vec3(uNormalMatrix * vertexNormal);

    /* Calcul position */
    gl_Position = uMVPMatrix * vertexPosition;
}