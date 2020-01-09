#ifndef WORLD_IMAKER_CUBEDATA_HPP 
#define WORLD_IMAKER_CUBEDATA_HPP

#include <glimac/common.hpp>

namespace glimac
{
    ///stock cube positions
    const ShapeVertex cubePositions[] = {
        //Position, tex coord, normal

        // Front
        ShapeVertex(glm::vec3(0.5, 0.5, 0.5), glm::vec2(1.0,1.0),glm::vec3(0, 0, 0.5)),
        ShapeVertex(glm::vec3(-0.5, 0.5, 0.5), glm::vec2(0.0,1.0),glm::vec3(0, 0, 0.5)),
        ShapeVertex(glm::vec3(-0.5, -0.5, 0.5), glm::vec2(0.0,0.0),glm::vec3(0, 0, 0.5)),
        ShapeVertex(glm::vec3(0.5, -0.5, 0.5), glm::vec2(1.0,0.0),glm::vec3(0, 0, 0.5)),
            
        // Right
        ShapeVertex(glm::vec3(0.5, 0.5, 0.5), glm::vec2(0.0,1.0),glm::vec3(0.5, 0, 0)),
        ShapeVertex(glm::vec3(0.5, -0.5, 0.5), glm::vec2(0.0,0.0),glm::vec3(0.5, 0, 0)),
        ShapeVertex(glm::vec3(0.5, -0.5, -0.5), glm::vec2(1.0,0.0),glm::vec3(0.5, 0, 0)),
        ShapeVertex(glm::vec3(0.5, 0.5, -0.5),glm::vec2(1.0,1.0),glm::vec3(0.5, 0, 0)),
        
        // Top	
        ShapeVertex(glm::vec3(0.5, 0.5, 0.5), glm::vec2(1.0,1.0),glm::vec3(0, 0.5, 0)),
        ShapeVertex(glm::vec3(0.5, 0.5, -0.5),glm::vec2(0.0,1.0),glm::vec3(0, 0.5, 0)),
        ShapeVertex(glm::vec3(-0.5, 0.5, -0.5),glm::vec2(0.0,0.0),glm::vec3(0, 0.5, 0)), 
        ShapeVertex(glm::vec3(-0.5, 0.5, 0.5), glm::vec2(0.0,1.0),glm::vec3(0, 0.5, 0)),

        // Left	
        ShapeVertex(glm::vec3(-0.5, 0.5, 0.5), glm::vec2(1.0,1.0),glm::vec3(-0.5, 0, 0)),
        ShapeVertex(glm::vec3(-0.5, 0.5, -0.5), glm::vec2(0.0,1.0),glm::vec3(-0.5, 0, 0)),
        ShapeVertex(glm::vec3(-0.5, -0.5, -0.5), glm::vec2(0.0,0.0),glm::vec3(-0.5, 0, 0)),
        ShapeVertex(glm::vec3(-0.5, -0.5, 0.5),  glm::vec2(1.0,0.0),glm::vec3(-0.5, 0, 0)),
        
        // Bottom
        ShapeVertex(glm::vec3(-0.5, -0.5, -0.5), glm::vec2(1.0,1.0),glm::vec3(0,-0.5, 0)),
        ShapeVertex(glm::vec3(0.5, -0.5, -0.5), glm::vec2(0.0,1.0),glm::vec3(0,-0.5, 0)),
        ShapeVertex(glm::vec3(0.5, -0.5, 0.5), glm::vec2(0.0,0.0),glm::vec3(0,-0.5, 0)),
        ShapeVertex(glm::vec3(-0.5, -0.5, 0.5), glm::vec2(1.0,0.0),glm::vec3(0,-0.5, 0)),

        // Back	
        ShapeVertex(glm::vec3(0.5, -0.5, -0.5), glm::vec2(1.0,0.0),glm::vec3(0, 0,-0.5)),
        ShapeVertex(glm::vec3(-0.5, -0.5, -0.5), glm::vec2(0.0,0.0),glm::vec3(0, 0,-0.5)),
        ShapeVertex(glm::vec3(-0.5, 0.5, -0.5), glm::vec2(0.0,1.0),glm::vec3(0, 0,-0.5)),
        ShapeVertex(glm::vec3(0.5, 0.5, -0.5),glm::vec2(1.0,1.0),glm::vec3(0, 0,-0.5))
    };
    
    ///stock cube indexes
    const unsigned short indexes[] = {
        0, 1, 2,   2, 3, 0,       // front
        4, 5, 6,   6, 7, 4,       // right
        8, 9, 10,  10,11,8,       // top
        12,13,14,  14,15,12,      // left
        16,17,18,  18,19,16,      // bottom
        20,21,22,  22,23,20		  // back
    };
}
#endif