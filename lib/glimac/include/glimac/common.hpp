#pragma once

#include <GL/glew.h>
#include "glm.hpp"

namespace glimac {

    constexpr int WINDOW_WIDTH = 1200;
    constexpr int WINDOW_HEIGHT = 1200;

    ///ShapeVertex structure
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
