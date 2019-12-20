#include <glimac/glm.hpp> 
#include "glimac/TrackballCamera.hpp"


namespace glimac {

    TrackballCamera::TrackballCamera():_fDistance(40.0f), _fAngleX(-40.0f), _fAngleY(-40.0f), _fAngleZ(0.f), _ViewMatrix(glm::mat4(1.f))
    {	
    }

    void TrackballCamera::moveFront(const float &delta) {
        _fDistance += delta;
    }

    void TrackballCamera::moveUp(const float &delta) {
        _fAngleY += delta;
    }

    void TrackballCamera::rotateLeft(const float &degrees) {
        _fAngleZ += degrees;
    }

    void TrackballCamera::rotateUp(const float &degrees){
      _fAngleX += degrees;
    }

    void TrackballCamera::defaultPosition(){
      _fDistance = 60.f;
      _fAngleX = -60.f;
      _fAngleZ = 0.f;
    }
    
    glm::mat4 TrackballCamera::getViewMatrix() const {
        glm::mat4 VM = glm::translate(_ViewMatrix, glm::vec3(0.f, 0.f, -_fDistance)); // Translation
        VM = glm::rotate(VM, glm::radians(_fAngleX), glm::vec3(1.f, 0.f, 0.f)); // Translation * Rotation
        VM = glm::rotate(VM, glm::radians(_fAngleZ), glm::vec3(0.f, 0.f, 1.f)); // Translation * Rotation * rotation
        VM = glm::translate(VM, glm::vec3(float(-10), float(-10), float(-10))); // pour centrer la caméra sur la scène
        return VM;
    }
    

    
    
}