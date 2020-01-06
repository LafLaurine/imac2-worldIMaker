#ifndef WORLD_IMAKER_CUBEDATA_HPP 
#define WORLD_IMAKER_CUBEDATA_HPP

#include <glimac/common.hpp>

namespace glimac
{
    ///stock cube positions
    
    const std::vector<glm::vec3> cubePositions = {
        // Front
        glm::vec3(0.5, 0.5, 0.5), glm::vec3(-0.5, 0.5, 0.5), glm::vec3(-0.5, -0.5, 0.5), glm::vec3(0.5, -0.5, 0.5),
        // Right
        glm::vec3(0.5, 0.5, 0.5), glm::vec3(0.5, -0.5, 0.5), glm::vec3(0.5, -0.5, -0.5), glm::vec3(0.5, 0.5, -0.5),
        // Top	
        glm::vec3(0.5, 0.5, 0.5), glm::vec3(0.5, 0.5, -0.5), glm::vec3(-0.5, 0.5, -0.5), glm::vec3(-0.5, 0.5, 0.5), 
        // Left	
        glm::vec3(-0.5, 0.5, 0.5), glm::vec3(-0.5, 0.5, -0.5), glm::vec3(-0.5, -0.5, -0.5), glm::vec3(-0.5, -0.5, 0.5),  
        // Bottom
        glm::vec3(-0.5, -0.5, -0.5), glm::vec3(0.5, -0.5, -0.5), glm::vec3(0.5, -0.5, 0.5), glm::vec3(-0.5, -0.5, 0.5), 
        // Back	
        glm::vec3(0.5, -0.5, -0.5), glm::vec3(-0.5, -0.5, -0.5), glm::vec3(-0.5, 0.5, -0.5), glm::vec3(0.5, 0.5, -0.5)
    };

    ///stock cube normals
    const std::vector<glm::vec3> normals = {
        glm::vec3(0, 0, 0.5), glm::vec3(0, 0, 0.5), glm::vec3(0, 0, 0.5), glm::vec3(0, 0, 0.5),
        glm::vec3(0.5, 0, 0), glm::vec3(0.5, 0, 0), glm::vec3(0.5, 0, 0), glm::vec3(0.5, 0, 0),
        glm::vec3(0, 0.5, 0), glm::vec3(0, 0.5, 0), glm::vec3(0, 0.5, 0), glm::vec3(0, 0.5, 0),
        glm::vec3(-0.5, 0, 0), glm::vec3(-0.5, 0, 0), glm::vec3(-0.5, 0, 0), glm::vec3(-0.5, 0, 0),
        glm::vec3(0,-0.5, 0), glm::vec3(0,-0.5, 0), glm::vec3(0,-0.5, 0), glm::vec3(0,-0.5, 0),
        glm::vec3(0, 0,-0.5), glm::vec3(0, 0,-0.5), glm::vec3(0, 0,-0.5), glm::vec3(0, 0,-0.5)
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