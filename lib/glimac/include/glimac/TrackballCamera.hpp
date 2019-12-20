#pragma once

#include <vector>
#include <memory>
#include <unordered_map>

#include "glm.hpp"
#include "FilePath.hpp"

namespace glimac {

class TrackballCamera {
private:
    float _fDistance; //distance par rapport au centre de la scène
    float _fAngleX; //angle de la cam autour de l'axe x : rotation haut et bas
    float _fAngleZ;
    float _fAngleY;
    glm::mat4 _ViewMatrix;

public:
    TrackballCamera();
    void moveFront(const float &delta);
    void moveUp(const float &delta);
    void rotateLeft(const float &degrees);
    void rotateUp(const float &degrees);
    glm::mat4 getViewMatrix() const;
    void defaultPosition();
};

}
