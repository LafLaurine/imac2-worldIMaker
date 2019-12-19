#version 330 core
out vec4 fragColor;

in vec3 vPos;
in vec3 vNormal;

uniform vec3 uKd;
uniform vec3 uKs;
uniform float uShininess;
uniform vec3 lightPos;
uniform vec3 uLightIntensity;

vec3 blinnPhong() {
    // Couleur=Li(Kd(wi˙N)+Ks(halfVector˙N)shininess)
    vec3 wi = normalize(lightPos);
    vec3 halfVector = normalize(-vPos);
    vec3 p1 = uKd*(dot(wi, vNormal));
    vec3 p2 = uKs*pow((dot(halfVector, vNormal)), uShininess);
    vec3 color =  uLightIntensity*(p1+p2);;
    return color;
}
void main() {
    fragColor = vec4(blinnPhong(), 1.0f);
}
