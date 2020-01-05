#include "glimac/Cube.hpp"
#include <glimac/gl-exception.hpp>
#include <iostream>

namespace glimac {

    Cube::Cube(glm::vec3 position): m_vao(0), m_ibo(0), m_position(position), m_color(1.0f,1.0f,1.0f,1.0f), m_visible(false), m_type(0) {
         initBuffer();
    }
    
    Cube::Cube() : m_vao(0), m_ibo(0), m_position(0), m_color(1.0f,1.0f,1.0f,1.0f), m_visible(false), m_type(0) {
        initBuffer();
    }


    void Cube::initBuffer() {
        //Vertex buffer position
        GLCall(glGenBuffers(1, &m_vbo));
        GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_vbo));    
        GLCall(glBufferData(GL_ARRAY_BUFFER,24 * sizeof(ShapeVertex), cubePositions,GL_STATIC_DRAW));
        GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
        
        GLuint cubeNormalVbo;
        GLCall(glGenBuffers(1, &cubeNormalVbo));
        GLCall(glBindBuffer(GL_ARRAY_BUFFER, cubeNormalVbo));    
        GLCall(glBufferData(GL_ARRAY_BUFFER,sizeof(normals), normals,GL_STATIC_DRAW));
        GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));

        //Vertex array
        GLCall(glGenVertexArrays(1, &m_vao));
        GLCall(glBindVertexArray(m_vao));
        // pos vao
        GLCall(glEnableVertexAttribArray(0));
        GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_vbo));
        GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const GLvoid*) offsetof(ShapeVertex, position)));
        GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));

        // normal vao
        GLCall(glEnableVertexAttribArray(1));
        GLCall(glBindBuffer(GL_ARRAY_BUFFER, cubeNormalVbo));
        GLCall(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), NULL));
        GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));

        //light vao
        unsigned int lightVAO;
        GLCall(glGenVertexArrays(1, &lightVAO));
        GLCall(glBindVertexArray(lightVAO));
        GLCall(glEnableVertexAttribArray(0));
        GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_vbo));
        GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), NULL));
        GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
        GLCall(glBindVertexArray(0));

        unsigned int textureVAO;
        GLCall(glGenVertexArrays(1, &textureVAO));
        GLCall(glBindVertexArray(textureVAO));
        // we only need to bind to the VBO, the container's VBO's data already contains the correct data.
        GLCall(glEnableVertexAttribArray(2));
        GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_vbo));
        GLCall(glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const GLvoid*) offsetof(ShapeVertex, texCoords)));
        GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
        GLCall(glBindVertexArray(0));

        //Index buffer
        GLCall(glGenBuffers(1, &m_ibo));
        GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo));
        GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexes), indexes, GL_STATIC_DRAW));
        GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
    }

    void Cube::draw(GLuint textureId) 
    {
        //if cube is not textured
        if(m_type == 0) {
            glEnable(GL_BLEND);
            glBindVertexArray(m_vao);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, (void*) 0);
            glBindVertexArray(0);
            glDisable(GL_BLEND);
        }
        //if cube is textured
        else if(m_type == 1){
            GLCall(glEnable(GL_BLEND));
            GLCall(glBindVertexArray(m_vao));
            GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo));
            GLCall(glActiveTexture(GL_TEXTURE3));
            GLCall(glBindTexture(GL_TEXTURE_2D, textureId));
            GLCall(glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, (void*) 0));
            GLCall(glActiveTexture(GL_TEXTURE3));
            GLCall(glBindTexture(GL_TEXTURE_2D, 0));
            GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
            GLCall(glBindVertexArray(0));
            GLCall(glDisable(GL_BLEND));
        }
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
    
    
}