#version 330

// Attributs de sommet
layout(location = 0) in vec3 aVertexPosition; // Position

// Matrices de transformations reçues en uniform
uniform mat4 uMVPMatrix;
uniform mat4 uMVMatrix;

void main() {
  gl_Position = uMVPMatrix * uMVMatrix * vec4(aVertexPosition, 1.0);
}