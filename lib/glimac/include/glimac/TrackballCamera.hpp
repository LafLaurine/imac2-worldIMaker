#pragma once

#include <vector>
#include <memory>
#include <unordered_map>

#include "glm.hpp"
#include "FilePath.hpp"

namespace glimac {

class TrackballCamera {
private:
    float _fDistance; ///distance from center of scene
    float _fAngleX; ///cam angle around x axis: up and down rotation
    float _fAngleZ;
    float _fAngleY;
    glm::mat4 _ViewMatrix;
    glm::vec3 m_position;

public:
    ///default constructor of trackballcamera
    TrackballCamera();
    ///move trackballcamera forward
    void moveFront(const float &delta);
    ///move trackballcamera up
    void moveUp(const float &delta);
    ///rotate left trackballcamera
    void rotateLeft(const float &degrees);
    ///rotate up trackballcamera
    void rotateUp(const float &degrees);
    ///rotate right trackball camera
    void rotateRight(const float &degrees);
    ///get position of trackball camera
    inline glm::vec3 getPosition() {return m_position;};
    ///get trackballcamera viewmatrix
    glm::mat4 getViewMatrix() const;
    ///set position of the trackballcamera
    void setPosMatrix(int l, int L, int H);
    ///set position by default of the trackballcamera
    void posDefault();
    ///set trackballcamera to the bottom
    void posBottom();
    ///set trackballcamera to the right
    void posRight();
    ///set trackballcamera to the left
    void posLeft();
};

}
