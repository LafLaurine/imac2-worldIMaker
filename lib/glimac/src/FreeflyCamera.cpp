#include <glimac/glm.hpp> 
#include "glimac/FreeFlyCamera.hpp"


namespace glimac {

    const double PI = 3.141592653589;
    const double HALF_PI = PI/2;

    FreeFlyCamera::FreeFlyCamera(): _position(glm::vec3(0.f, 0.f, 0.f)), _fPhi(PI), _fTheta(0) {
        computeDirectionVectors();	
    }
    
    void FreeFlyCamera::computeDirectionVectors() {
        _frontVector = glm::vec3(std::cos(_fTheta) * std::sin(_fPhi),std::sin(_fTheta),std::cos(_fTheta) * std::cos(_fPhi));
        _leftVector = glm::vec3(std::sin(_fPhi + HALF_PI),0,std::cos(_fPhi + HALF_PI));
        _upVector = glm::cross(_frontVector,_leftVector);
    }

    void FreeFlyCamera::moveLeft(float t) {
        _position += t * _leftVector;
        _upVector = glm::cross(_frontVector,_leftVector);
    }

    void FreeFlyCamera::moveFront(float t) {
        _position += t * _frontVector;
        _upVector = glm::cross(_frontVector,_leftVector);
    }

    void FreeFlyCamera::rotateLeft(float degrees) {
        _fTheta += glm::radians(degrees);
        _frontVector = glm::vec3(std::cos(_fTheta) * std::sin(_fPhi),std::sin(_fTheta),std::cos(_fTheta) * std::cos(_fPhi));
        _leftVector = glm::vec3(std::sin(_fPhi + HALF_PI),0,std::cos(_fPhi + HALF_PI));
    }

    void FreeFlyCamera::rotateUp(float degrees) {
        _fPhi += glm::radians(degrees);
        _frontVector = glm::vec3(std::cos(_fTheta) * std::sin(_fPhi),std::sin(_fTheta),std::cos(_fTheta) * std::cos(_fPhi));
        _leftVector = glm::vec3(std::sin(_fPhi + HALF_PI),0,std::cos(_fPhi + HALF_PI));
    }

    glm::mat4 FreeFlyCamera::getViewMatrix() const {
        //premier arg : position caméra exprimée dans le monde (eye)
        //2eme arg : point que la caméra regarde (point)
        //Dernier arg : axe vertical caméra (up)
        return glm::lookAt(_position,_position+_frontVector, _upVector);
    }
    
}