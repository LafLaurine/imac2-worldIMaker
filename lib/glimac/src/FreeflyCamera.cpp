#include <glimac/glm.hpp> 
#include "glimac/FreeFlyCamera.hpp"
#include <iostream>

namespace glimac {

    constexpr double PI = 3.141592653589;
    constexpr double HALF_PI = PI/2;
    
    //freefly constructor
    FreeFlyCamera::FreeFlyCamera(): m_position(glm::vec3(10.f, 5.f, 35.f)), m_fPhi(PI), m_fTheta(0) {
        computeDirectionVectors();	
    }   
    
    void FreeFlyCamera::computeDirectionVectors() {
        float radPhi = m_fPhi;
        float radTheta = m_fTheta;

        m_frontVector = glm::vec3(cos(radTheta)*sin(radPhi), sin(radTheta), cos(radTheta)*cos(radPhi));
        m_frontVectorFixed = glm::vec3(sin(radPhi), 0, cos(radPhi));
        m_leftVector = glm::vec3(sin(radPhi+(M_PI/2.0)), 0, cos(radPhi+(M_PI/2.0)));

        m_upVector = glm::cross(m_frontVector, m_leftVector);
    }

    void FreeFlyCamera::moveLeft(float t) {
        m_position += t * m_leftVector;
        computeDirectionVectors();
    }

    void FreeFlyCamera::moveFront(float t) {
        m_position += t * m_frontVectorFixed;
        computeDirectionVectors();
    }

    void FreeFlyCamera::moveUp(float t) {
        m_position += t * m_upVector;
        computeDirectionVectors();
    }

    void FreeFlyCamera::rotateLeft(float degrees) {
        m_fPhi += glm::radians(degrees);
        computeDirectionVectors();
    }

    void FreeFlyCamera::rotateUp(float degrees) {
        m_fTheta += glm::radians(degrees);
        computeDirectionVectors();
    }

    glm::mat4 FreeFlyCamera::getViewMatrix() const {
        // first argument: camera position expressed in the world (eye)
        // 2nd argument: point the camera is looking at (point)
        // Last argument: vertical camera ax (top)
        return glm::lookAt(m_position,m_position+m_frontVector, m_upVector);
    }
}