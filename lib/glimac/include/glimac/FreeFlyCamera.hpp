#pragma once

#include <vector>
#include <memory>
#include <unordered_map>

#include "glm.hpp"
#include "FilePath.hpp"

namespace glimac {

class FreeFlyCamera {
private:
    //position caméra
    glm::vec3 m_position;
    //coordonnées sphériques du vecteur
    float m_fPhi;
    float m_fTheta;
    glm::vec3 m_frontVector;
    glm::vec3 m_leftVector;
    glm::vec3 m_upVector;

public:
    FreeFlyCamera();
    ~FreeFlyCamera() = default;
    void computeDirectionVectors();
    void moveLeft(float t);
    void moveFront(float t);
    void rotateLeft(float degrees);
    void rotateUp(float degrees);
    glm::mat4 getViewMatrix() const;
};

}
