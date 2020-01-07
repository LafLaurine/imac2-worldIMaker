#version 330 core
out vec4 fragColor;

in vec3 vPos;
in vec3 vNormal;

uniform mat4 uNormalMat;
uniform vec3 uColor;

in vec2 vTexCoords;
uniform sampler2D uTexture;
uniform bool setTexture;
uniform int uCubeType;

vec3 uKd;
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
	if(setTexture && uCubeType == 1) {
		uKd = texture(uTexture, vTexCoords).rbg;
	}
	else {
		uKd = vec3(0.6,0.6,0.6);
	}
	return (uLightIntensityP / (d * d)) * ( uKd * ( dot(w_i, normal_vs ) ) + uKs * ( pow( dot(halfVector, normal_vs), uShininess ) ) );
}

vec3 blinnPhongD(vec3 position_vs, vec3 normal_vs){

	vec3 w_zero = normalize(-position_vs);
	vec3 w_i = normalize(-uLightDir_vs);
	vec3 halfVector = (w_zero + w_i) / 2;
	if(setTexture && uCubeType == 1) {
		uKd = texture(uTexture, vTexCoords).rgb;
	}
	else {
		uKd = vec3(0.6,0.6,0.6);
	}
	return uLightIntensityD * ( uKd * ( dot(w_i, normal_vs ) ) + uKs * ( pow( dot(halfVector, normal_vs), uShininess ) ) );
}

void main() {
	vec3 lum = (blinnPhongP(vPos, normalize(vNormal)) + blinnPhongD(vPos, normalize(vNormal)));
	vec3 totalLuminosity = min(lum + ambiantLightIntensity, 1.);
    vec3 normal = (uNormalMat * vec4(vNormal, 0.)).xyz;
    vec3 color = uColor;
	vec4 tex = texture(uTexture, vTexCoords);
	if(setTexture && uCubeType == 1) {
		fragColor = vec4(tex.rgb * totalLuminosity, 1.0f);
	}
	else if((setTexture && uCubeType == 0) || (!setTexture && uCubeType == 0)){
		fragColor = vec4(totalLuminosity  * color, 1.0f);
		fragColor.a = 0.6;
	}
}
