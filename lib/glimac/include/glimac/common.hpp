#pragma once

#include <glimac/glm.hpp> 
#include <GL/glew.h>
#include <list>
#include <vector>
#include "glm.hpp"

namespace glimac {

    constexpr int WINDOW_WIDTH = 1200;
    constexpr int WINDOW_HEIGHT = 1200;
    constexpr double PI = 3.141592653589;
    constexpr double HALF_PI = PI/2;

	static constexpr unsigned int m_height = 20;
	static constexpr unsigned int m_width = 20;
	static constexpr unsigned int m_length = 20;

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
