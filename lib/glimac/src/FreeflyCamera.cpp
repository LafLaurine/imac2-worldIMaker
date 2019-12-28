#include <glimac/glm.hpp> 
#include "glimac/FreeFlyCamera.hpp"
#include <iostream>

namespace glimac {
    
    //set pi and half pi
    constexpr double PI = 3.141592653589;
    constexpr double HALF_PI = PI/2;

    //freefly constructor
    FreeFlyCamera::FreeFlyCamera(): m_position(glm::vec3(0.f, 0.f, 10.f)), m_fPhi(PI), m_fTheta(0) {
        computeDirectionVectors();	
    }
    
    void FreeFlyCamera::computeDirectionVectors() {
        //compute direction vectors
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
        // first argument: camera position expressed in the world (eye)
        // 2nd argument: point the camera is looking at (point)
        // Last argument: vertical camera ax (top)
        return glm::lookAt(m_position,m_position+m_frontVector, m_upVector);
    }
    
}