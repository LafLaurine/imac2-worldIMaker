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
    float _fAngleY; //angle de la cam autour de l'axe y : rotation gauche et droite

public:
    TrackballCamera();
    void moveFront(const float &delta);
    void rotateLeft(const float &degrees);
    void rotateRight(const float &degrees);
    glm::mat4 getViewMatrix() const;
};

}
