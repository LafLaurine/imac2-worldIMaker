#version 330 core
out vec4 fragColor;

in vec3 vPos;
in vec3 vNormal;

uniform mat4 uNormalMat;
uniform vec3 uColor;

uniform vec3 uKd;
uniform vec3 uKs;
uniform float uShininess;
uniform vec3 uLightPos_vs;
uniform vec3 uLightDir_vs;
uniform vec3 uLightIntensityP;
uniform vec3 uLightIntensityD;
uniform vec3 ambiantLightIntensity;

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
	vec3 totalLuminosity = min(lum + ambiantLightIntensity, 1.);
    vec3 normal = (uNormalMat * vec4(vNormal, 0.)).xyz;
    vec3 color = uColor;
    fragColor = vec4(totalLuminosity  * color, 1.0f);
}
