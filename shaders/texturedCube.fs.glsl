#version 330 core

in vec3 vPos;
in vec3 vNormal;

uniform mat4 uNormalMat;

in vec2 vTexCoords;
uniform sampler2D uTexture;
uniform vec3 uKd;
uniform vec3 uKs;
uniform float uShininess;
uniform vec3 uLightPos_vs;
uniform vec3 uLightDir_vs;
uniform vec3 uLightIntensityP;
uniform vec3 uLightIntensityD;

out vec3 fFragTex;

vec3 blinnPhongP(vec3 position_vs, vec3 normal_vs){
    float d = distance(uLightPos_vs, vPos);
	vec3 w_zero = normalize(-position_vs);
	vec3 w_i = (normalize(uLightPos_vs - vPos));
	vec3 halfVector = (w_zero + w_i) / 2;
	return (uLightIntensityP / (d * d)) * ( uKd * ( dot(w_i, normal_vs ) ) + uKs * ( pow( dot(halfVector, normal_vs), uShininess ) ) );
}

vec3 blinnPhongD(vec3 position_vs, vec3 normal_vs){

	vec3 w_zero = normalize(-position_vs);
	vec3 w_i = normalize(-uLightDir_vs);
	vec3 halfVector = (w_zero + w_i) / 2;

	return uLightIntensityD * ( uKd * ( dot(w_i, normal_vs ) ) + uKs * ( pow( dot(halfVector, normal_vs), uShininess ) ) );
}

void main() {
    vec3 lum = (blinnPhongP(vPos, normalize(vNormal)) + blinnPhongD(vPos, normalize(vNormal)));
    vec3 normal = (uNormalMat * vec4(vNormal, 0.)).xyz;
    fFragTex = texture(uTexture, vTexCoords).xyz  * lum;
}