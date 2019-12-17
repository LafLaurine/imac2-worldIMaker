#include "glimac/Cube.hpp"

namespace glimac {

    const float cubePositions[] = {
        // v0
        0.5,  0.5,  0.5,
        // v1
        -0.5,  0.5,  0.5,
        // v2
        -0.5, -0.5,  0.5,
        // v3
        0.5, -0.5,  0.5,
        // v4
        0.5, -0.5, -0.5,
        // v5
        0.5,  0.5, -0.5,
        // v6
        -0.5,  0.5, -0.5,
        // v7
        -0.5, -0.5, -0.5,
    };

    const unsigned short indices[] = {
        // face de devant : v0, v1, v2 puis v0, v2, v3
        0, 1, 2,  0, 2, 3,
        // face de derrière
        4, 7, 6,  4, 6, 5,
        // face de gauche
        1, 6, 7,  1, 7, 2,
        // face de droite
        0, 3, 4,  0, 4, 5,
        // face de dessous
        2, 7, 4,  2, 4, 3,
        // face de dessus
        0, 5, 6,  0, 6, 1
        };


    void Cube::initBuffer() {
        GLuint cubeVbo;
        //Vertex buffer
        glGenBuffers(1, &cubeVbo);
        glBindBuffer(GL_ARRAY_BUFFER, cubeVbo);    
        glBufferData(GL_ARRAY_BUFFER,
                sizeof(cubePositions), cubePositions,
                GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        //Vertex array
        glGenVertexArrays(1, &m_vao);
        glBindVertexArray(m_vao);
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, cubeVbo);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), NULL);
        glBindVertexArray(0);

        //Index buffer
        glGenBuffers(1, &m_ibo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        glBindVertexArray(m_vao);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
    }


    Cube::Cube() : m_vao(0), m_ibo(0), m_position(0) {
        initBuffer();
    }

    void Cube::draw() {
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, (void*) 0);
    }
}