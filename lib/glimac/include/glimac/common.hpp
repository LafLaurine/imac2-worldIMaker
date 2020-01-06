#pragma once

#include <GL/glew.h>
#include "glm.hpp"

namespace glimac {

struct ShapeVertex{
    glm::vec3 position;
    glm::vec2 texCoords;

    ShapeVertex(){
        this->position.x = 0;
        this->position.y = 0;
        this->position.z = 0;
        this->texCoords.x = 0;
        this->texCoords.y = 0;
    }

    ShapeVertex(glm::vec3 position, glm::vec2 texCoords)
    : position(position), texCoords(texCoords)
    {
    }

};


}
