#include "glimac/Cube.hpp"
#include <glimac/gl-exception.hpp>

namespace glimac {

    glm::vec3 cubePositions[] = {
        // Front v0,v1,v2,v3
        glm::vec3(0.5, 0.5, 0.5), glm::vec3(-0.5, 0.5, 0.5), glm::vec3(-0.5, -0.5, 0.5), glm::vec3(0.5, -0.5, 0.5),
        // Right v0,v3,v4,v5
        glm::vec3(0.5, 0.5, 0.5), glm::vec3(0.5, -0.5, 0.5), glm::vec3(0.5, -0.5, -0.5), glm::vec3(0.5, 0.5, -0.5),
        // Top v0,v5,v6,v0.5	
        glm::vec3(0.5, 0.5, 0.5), glm::vec3(0.5, 0.5, -0.5), glm::vec3(-0.5, 0.5, -0.5), glm::vec3(-0.5, 0.5, 0.5), 
        // Left v0.5,v6,v7,v2	
        glm::vec3(-0.5, 0.5, 0.5), glm::vec3(-0.5, 0.5, -0.5), glm::vec3(-0.5, -0.5, -0.5), glm::vec3(-0.5, -0.5, 0.5),  
        // Bottom v7,v4,v3,v2
        glm::vec3(-0.5, -0.5, -0.5), glm::vec3(0.5, -0.5, -0.5), glm::vec3(0.5, -0.5, 0.5), glm::vec3(-0.5, -0.5, 0.5), 
        // Back v4,v7,v6,v5	
        glm::vec3(0.5, -0.5, -0.5), glm::vec3(-0.5, -0.5, -0.5), glm::vec3(-0.5, 0.5, -0.5), glm::vec3(0.5, 0.5, -0.5)
    };

    const glm::vec3 normals[] = {
        glm::vec3(0, 0, 0.5), glm::vec3(0, 0, 0.5), glm::vec3(0, 0, 0.5), glm::vec3(0, 0, 0.5),
        glm::vec3(0.5, 0, 0), glm::vec3(0.5, 0, 0), glm::vec3(0.5, 0, 0), glm::vec3(0.5, 0, 0),
        glm::vec3(0, 0.5, 0), glm::vec3(0, 0.5, 0), glm::vec3(0, 0.5, 0), glm::vec3(0, 0.5, 0),
        glm::vec3(-0.5, 0, 0), glm::vec3(-0.5, 0, 0), glm::vec3(-0.5, 0, 0), glm::vec3(-0.5, 0, 0),
        glm::vec3(0,-0.5, 0), glm::vec3(0,-0.5, 0), glm::vec3(0,-0.5, 0), glm::vec3(0,-0.5, 0),
        glm::vec3(0, 0,-0.5), glm::vec3(0, 0,-0.5), glm::vec3(0, 0,-0.5), glm::vec3(0, 0,-0.5)
    };

    const unsigned short indices[] = {
        0, 1, 2,   2, 3, 0,       // front
        4, 5, 6,   6, 7, 4,       // right
        8, 9, 10,  10,11,8,       // top
        12,13,14,  14,15,12,      // left
        16,17,18,  18,19,16,      // bottom
        20,21,22,  22,23,20		  // back
    };


    Cube::Cube(glm::vec3 position): m_vao(0), m_ibo(0), m_position(position), m_color(glm::vec3(0,0,1)), m_visible(false) {
         initBuffer();
    }


    void Cube::initBuffer() {
          //Vertex buffer position
          GLCall(glGenBuffers(1, &m_vbo));
          GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_vbo));    
          GLCall(glBufferData(GL_ARRAY_BUFFER,
                  sizeof(cubePositions), cubePositions,
                  GL_STATIC_DRAW));
          GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
          GLuint cubeNormalVbo;
          //Vertex buffer position
          GLCall(glGenBuffers(1, &cubeNormalVbo));
          GLCall(glBindBuffer(GL_ARRAY_BUFFER, cubeNormalVbo));    
          GLCall(glBufferData(GL_ARRAY_BUFFER,
                  sizeof(normals), normals,
                  GL_STATIC_DRAW));
          GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));

         //Vertex array
        glGenVertexArrays(1, &m_vao);
        glBindVertexArray(m_vao);
        // pos vao
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), NULL);
        // normal vao
        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, cubeNormalVbo);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), NULL);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
        //light vao
        unsigned int lightVAO;
        glGenVertexArrays(1, &lightVAO);
        glBindVertexArray(lightVAO);
        // we only need to bind to the VBO, the container's VBO's data already contains the correct data.
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
        // set the vertex attributes (only position data for our lamp)
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        //Index buffer
        glGenBuffers(1, &m_ibo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }


    Cube::Cube() : m_vao(0), m_ibo(0), m_position(0), m_color(0), m_visible(false) {
        initBuffer();
    }

    void Cube::draw() {
      glBindVertexArray(m_vao);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
      glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, (void*) 0);
      glBindVertexArray(0);
    }
    
    void Cube::setVisible() {
        if(m_visible == false){
            m_visible = true;
        }
    }

    void Cube::setInvisible() {
        if(m_visible == true){
            m_visible = false;
        }
    }

    void Cube::editColor(int type) {
    switch (type) {
      case 0: m_color = glm::vec3(1,0,0);
        break;
      case 1: m_color = glm::vec3(0,1,0);
        break;
      case 2: m_color = glm::vec3(0,0,1);
        break;
      case 3: m_color = glm::vec3(0,1,1);
        break;
      default : break;
    }
  }
}