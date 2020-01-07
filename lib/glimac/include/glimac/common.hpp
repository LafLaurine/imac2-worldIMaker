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
    
    constexpr GLuint VERTEX_ATTR_POSITION = 0;
    constexpr GLuint VERTEX_ATTR_NORMAL = 1;
    constexpr GLuint VERTEX_ATTR_TEXT = 2;

    ///ShapeVertex structure
    struct ShapeVertex{
        glm::vec3 position;
        glm::vec2 texCoords;
        glm::vec3 normals;

        ShapeVertex() = default;
        ShapeVertex(const glm::vec3 &position, const glm::vec2 &texCoords, const glm::vec3 &normals)
        : position(position), texCoords(texCoords), normals(normals)
        {
        }

    };
}
