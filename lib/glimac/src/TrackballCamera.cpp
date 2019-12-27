#include <glimac/glm.hpp> 
#include "glimac/TrackballCamera.hpp"


namespace glimac {

    TrackballCamera::TrackballCamera():_fDistance(30.0f), _fAngleX(0.0f),_fAngleZ(0.f),_fAngleY(0.0f), _ViewMatrix(glm::mat4(1.f)),  m_position(0.f, 0.f, 0.f)
    {	
    }


    void TrackballCamera::posDefault()
    {
        _fDistance = 30.0f;
        _fAngleX = 0.0f;
        _fAngleZ = 0.0f;
    }

    void TrackballCamera::posBottom() {
        _fDistance = 40.0f;
        _fAngleX = 180.0f;
    }

    void TrackballCamera::posLeft() {
        _fDistance = 30.0f;
        _fAngleX = -90.0f;
        _fAngleZ = 90.0f;
    }

    void TrackballCamera::moveFront(const float &delta) {
        _fDistance += delta;
    }

    void TrackballCamera::moveUp(const float &delta) {
        _fAngleY += delta;
    }

        
    void TrackballCamera::rotateRight(const float &degrees) 
    {
        _fAngleY += degrees;
    }

    void TrackballCamera::rotateLeft(const float &degrees) {
        _fAngleZ += degrees;
    }

    void TrackballCamera::rotateUp(const float &degrees){
      _fAngleX += degrees;
    }
    
    glm::mat4 TrackballCamera::getViewMatrix() const {
        glm::mat4 VM = glm::translate(_ViewMatrix, glm::vec3(0.f, 0.f, -_fDistance)); // Translation
        VM = glm::rotate(VM, glm::radians(_fAngleX), glm::vec3(1.f, 0.f, 0.f)); // Translation * Rotation
        VM = glm::rotate(VM, glm::radians(_fAngleZ), glm::vec3(0.f, 0.f, 1.f)); // Translation * Rotation * rotation
        VM = glm::translate(VM, -m_position); // pour centrer la caméra sur la scène
        return VM;
    }


    void TrackballCamera::setPosMatrix(int l, int L, int H)
    {
        m_position = glm::vec3(l,L,H);
    }
    


    
    
}