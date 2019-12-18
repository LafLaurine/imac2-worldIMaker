#include "glimac/Cube.hpp"
#include <iostream>

#include "glimac/gl-exception.hpp"

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

/*    const glm::vec3 normals[] = {
        glm::vec3(0, 0, 1), glm::vec3(0, 0, 1), glm::vec3(0, 0, 1), glm::vec3(0, 0, 1),
        glm::vec3(1, 0, 0), glm::vec3(1, 0, 0), glm::vec3(1, 0, 0), glm::vec3(1, 0, 0),
        glm::vec3(0, 1, 0), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0),
        glm::vec3(-1, 0, 0), glm::vec3(-1, 0, 0), glm::vec3(-1, 0, 0), glm::vec3(-1, 0, 0),
        glm::vec3(0,-1, 0), glm::vec3(0,-1, 0), glm::vec3(0,-1, 0), glm::vec3(0,-1, 0),
        glm::vec3(0, 0,-1), glm::vec3(0, 0,-1), glm::vec3(0, 0,-1), glm::vec3(0, 0,-1)
    };*/

    Cube::Cube(glm::vec3 position): m_vao(0), m_ibo(0), m_position(position), m_color(0.2f,0.2f,0.5f), m_invisible(0) {
         initBuffer();
    }

    void Cube::initBuffer() {

        std::unique_ptr<Image> textureEarth = loadImage("./assets/textures/EarthMap.jpg");
        if (textureEarth == NULL ) std::cout << "Texture couldn't be loaded" << std::endl;
        GLuint m_vbo;
        GLCall(glGenBuffers(1, &m_vbo));

        GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_vbo));

        GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(cubePositions),cubePositions, GL_STATIC_DRAW));

        GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));

        //GLuint m_ibo;
        GLCall(glGenBuffers(1, &m_ibo));

        //binder du GL_ELEMENT_ARRAY_BUFFER réservé pour les ibo
        GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo));

        GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW));

        GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
        
        //GLuint vao;
        GLCall(glGenVertexArrays(1, &m_vao));
        GLCall(glBindVertexArray(m_vao));
        const GLuint VERTEX_ATTR_POSITION = 0;
        const GLuint VERTEX_ATTR_NORMAL = 1;
       // const GLuint VERTEX_ATTR_TEXT = 1;

        GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_vbo)); // on binde le m_vbo
        // Vertex input description
        GLCall(glEnableVertexAttribArray(VERTEX_ATTR_POSITION));
        GLCall(glVertexAttribPointer(VERTEX_ATTR_POSITION, 3, GL_FLOAT, GL_FALSE,3 * sizeof(float), 0));

        GLCall(glEnableVertexAttribArray(VERTEX_ATTR_NORMAL));
        GLCall(glVertexAttribPointer(VERTEX_ATTR_NORMAL, 3, GL_FLOAT, GL_FALSE,3 * sizeof(float), 0));

       /* GLCall(glEnableVertexAttribArray(VERTEX_ATTR_TEXT));
        GLCall(glVertexAttribPointer(VERTEX_ATTR_TEXT, 3, GL_FLOAT, GL_FALSE,3 * sizeof(float), 0));*/

        GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
        GLCall(glBindVertexArray(0));

        
        /*glGenTextures(2,&texId);
        glBindTexture(GL_TEXTURE_2D, texId);

        glTexImage2D(GL_TEXTURE_2D,
        0,
        GL_RGBA, //internalFormat
        textureEarth->getWidth(), // Width
        textureEarth->getHeight(), // Height
        0, 
        GL_RGBA, // Format
        GL_FLOAT, // Type
        textureEarth->getPixels() // tab pixel
        );
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glBindTexture(GL_TEXTURE_2D, 0);*/
        }

    Cube::Cube() : m_vao(0), m_ibo(0), m_position(0), m_color(0.2f,0.2f,0.5f), m_invisible(0) {
        initBuffer();
    }

    void Cube::draw() {
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, (void*) 0);
    }
}