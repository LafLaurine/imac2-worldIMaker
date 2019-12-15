#version 330

// Attributs de sommet
layout(location = 0) in vec3 aVertexPosition; // Position
layout(location = 1) in vec3 aVertexNormal;

// Matrices de transformations reçues en uniform
uniform mat4 uMVPMatrix;
uniform mat4 uMVMatrix;
uniform mat4 uNormalMatrix;


out vec3 vPosition_vs;
out vec3 vNormal_vs; 

void main() {
  //homogenous coordinates
	vec4 vertexPosition = vec4(aVertexPosition, 1);
	vec4 vertexNormal = vec4(aVertexNormal, 0);

	//out values
	vPosition_vs = vec3(uMVMatrix * vertexPosition);
	vNormal_vs = vec3(uNormalMatrix * vertexNormal);

	//project position
	gl_Position = uMVPMatrix * vertexPosition;
}