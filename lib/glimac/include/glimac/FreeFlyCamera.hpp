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
    glm::vec3 _position;
    //coordonnées sphériques du vecteur
    float _fPhi;
    float _fTheta;
    glm::vec3 _frontVector;
    glm::vec3 _leftVector;
    glm::vec3 _upVector;

public:
    FreeFlyCamera();
    void computeDirectionVectors();
    void moveLeft(float t);
    void moveFront(float t);
    void rotateLeft(float degrees);
    void rotateUp(float degrees);
    glm::mat4 getViewMatrix() const;
};

}
