#pragma once

#include <vector>
#include <memory>
#include <unordered_map>

#include "glm.hpp"
#include "FilePath.hpp"

namespace glimac {

class FreeFlyCamera {
private:
    ///camera position
    glm::vec3 m_position;
    ///spherical coordinates
    float m_fPhi;
    float m_fTheta;
    ///vector coordonates
    glm::vec3 m_frontVector;
    glm::vec3 m_frontVectorFixed;
    glm::vec3 m_leftVector;
    glm::vec3 m_upVector;

public:
    ///default constructor of FreeFlyCamera
    FreeFlyCamera();
    ///default destructor of FreeFlyCamera
    ~FreeFlyCamera() = default;
    ///compute direction vectors
    void computeDirectionVectors();
    ///move camera to the left
    void moveLeft(float t);
    ///move camera forward
    void moveFront(float t);
    ///rotate camera to the left
    void rotateLeft(float degrees);
    ///rotate camera up
    void rotateUp(float degrees);
    ///move camera up
    void moveUp(float t);
    ///get view matrix of the camera
    glm::mat4 getViewMatrix() const;
};

}
