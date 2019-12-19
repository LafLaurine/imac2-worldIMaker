#include <glimac/glm.hpp> 
#include "glimac/FreeFlyCamera.hpp"
#include <iostream>

namespace glimac {

    const double PI = 3.141592653589;
    const double HALF_PI = PI/2;

    FreeFlyCamera::FreeFlyCamera(): m_position(glm::vec3(0.f, 0.f, 10.f)), m_fPhi(PI), m_fTheta(0) {
        computeDirectionVectors();	
    }
    
    void FreeFlyCamera::computeDirectionVectors() {
        m_frontVector = glm::vec3(std::cos(m_fTheta) * std::sin(m_fPhi),std::sin(m_fTheta),std::cos(m_fTheta) * std::cos(m_fPhi));
        m_leftVector = glm::vec3(std::sin(m_fPhi + HALF_PI),0,std::cos(m_fPhi + HALF_PI));
        m_upVector = glm::cross(m_frontVector,m_leftVector);
    }

    void FreeFlyCamera::moveLeft(float t) {
        m_position += t * m_leftVector;
        m_upVector = glm::cross(m_frontVector,m_leftVector);
    }

    void FreeFlyCamera::moveFront(float t) {
        m_position += t * m_frontVector;
        m_upVector = glm::cross(m_frontVector,m_leftVector);
    }

    void FreeFlyCamera::rotateLeft(float degrees) {
        m_fTheta += glm::radians(degrees);
        m_frontVector = glm::vec3(std::cos(m_fTheta) * std::sin(m_fPhi),std::sin(m_fTheta),std::cos(m_fTheta) * std::cos(m_fPhi));
        m_leftVector = glm::vec3(std::sin(m_fPhi + HALF_PI),0,std::cos(m_fPhi + HALF_PI));
    }

    void FreeFlyCamera::rotateUp(float degrees) {
        m_fPhi += glm::radians(degrees);
        m_frontVector = glm::vec3(std::cos(m_fTheta) * std::sin(m_fPhi),std::sin(m_fTheta),std::cos(m_fTheta) * std::cos(m_fPhi));
        m_leftVector = glm::vec3(std::sin(m_fPhi + HALF_PI),0,std::cos(m_fPhi + HALF_PI));
    }

    glm::mat4 FreeFlyCamera::getViewMatrix() const {
        //premier arg : position caméra exprimée dans le monde (eye)
        //2eme arg : point que la caméra regarde (point)
        //Dernier arg : axe vertical caméra (up)
        return glm::lookAt(m_position,m_position+m_frontVector, m_upVector);
    }
    
}