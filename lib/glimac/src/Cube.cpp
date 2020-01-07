#include "glimac/Cube.hpp"
#include <glimac/gl-exception.hpp>
#include <iostream>

namespace glimac {
  
  Cube::Cube(glm::ivec3 position): m_vao(0), m_ibo(0), m_position(position), m_color(1.0f,1.0f,1.0f,1.0f), m_type(0) {
    initBuffer();
  }
  
  Cube::Cube(glm::ivec3 position, glm::vec4 color): m_vao(0), m_ibo(0), m_position(position), m_color(color), m_type(0) {
    initBuffer();
  }
  
  Cube::Cube() : m_vao(0), m_ibo(0), m_position(0), m_color(1.0f,1.0f,1.0f,1.0f), m_type(0) {
    initBuffer();
  }
  
  void Cube::initBuffer() {
      //Vertex buffer position
      GLCall(glGenBuffers(1, &m_vbo));
      GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_vbo));    
      GLCall(glBufferData(GL_ARRAY_BUFFER,24 * sizeof(ShapeVertex), cubePositions,GL_STATIC_DRAW));
      GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));

      //Vertex array
      GLCall(glGenVertexArrays(1, &m_vao));
      GLCall(glBindVertexArray(m_vao));
      // pos vao
      GLCall(glEnableVertexAttribArray(0));
      GLCall(glEnableVertexAttribArray(1));
      GLCall(glEnableVertexAttribArray(2));
      GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_vbo));
      GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const GLvoid*) offsetof(ShapeVertex, position)));
      GLCall(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const GLvoid*) offsetof(ShapeVertex, normals)));
      GLCall(glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const GLvoid*) offsetof(ShapeVertex, texCoords)));
      GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
      GLCall(glBindVertexArray(m_vao));

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

    //redefine operator ==
    bool Cube::operator==(Cube cube) {
    if (m_position == cube.m_position) {
      return true;
    }
    else {
      return false;
    }
  }
    
    
}