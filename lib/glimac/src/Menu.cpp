#include <iostream>
#include <string>
#include <glimac/Menu.hpp>
#include <GL/glew.h>

namespace glimac {
    const VertexTex vertices[] = { 
        VertexTex(glm::vec2(-1.f, 1.f), 
                glm::vec2(0.f, 0.f)),
        VertexTex(glm::vec2(1.f, 1.f), 
                glm::vec2(1.f, 0.f)),
        VertexTex(glm::vec2(1.f, -1.f),
                glm::vec2(1.f, 1.f)),
        VertexTex(glm::vec2(-1.f, -1.f), 
                glm::vec2(0.f, 1.f))
    };

    const uint32_t indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    Menu::Menu(Scene &scene, ProgramType type):m_ibo(0),m_vbo(0),m_vao(0),m_texture(Texture("truc.jpg")), m_scene(scene), m_type(type)
    {
        scene.loadProgram(type,"../shaders/texture.vs.glsl","../shaders/texture.fs.glsl");
        const GLuint VERTEX_ATTR_POSITION = 0;
        const GLuint VERTEX_ATTR_TEXCOORD = 1;

        glGenBuffers(1, &m_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo); //Binder la VBO

        glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(VertexTex), vertices, GL_STATIC_DRAW);

        glBindBuffer(GL_ARRAY_BUFFER, 0); // debinder la VBO

        glGenBuffers(1, &m_ibo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
        //On a 36 points
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, 36*sizeof(uint32_t), indices, GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        glGenVertexArrays(1, &m_vao);
        glBindVertexArray(m_vao); //Binder la VAO

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);

        glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
        glEnableVertexAttribArray(VERTEX_ATTR_TEXCOORD);

        glBindBuffer(GL_ARRAY_BUFFER, m_vbo); //Binder la VBO
        glVertexAttribPointer(VERTEX_ATTR_POSITION, 2, GL_FLOAT, GL_FALSE, sizeof(VertexTex), (const GLvoid*) offsetof(VertexTex, position));
        glVertexAttribPointer(VERTEX_ATTR_TEXCOORD, 2, GL_FLOAT, GL_FALSE, sizeof(VertexTex), (const GLvoid*) offsetof(VertexTex, texCoords));
        glBindBuffer(GL_ARRAY_BUFFER, 0); // debinder la VBO

        glBindVertexArray(0); //Debinder la VAO
    }
    
    void Menu::draw(Scene &scene, ProgramType type){
        scene.useProgram(type);
        glUniform1i(scene.uTextureLocation,0);
        glGenTextures(1, &m_texture.m_textureId);
		glBindTexture(GL_TEXTURE_2D, m_texture.m_textureId);
        glBindVertexArray(m_vao); //Binder la VAO
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
        glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*) 0, 1);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glBindVertexArray(0); //Debinder la VAO
        glBindTexture(GL_TEXTURE_2D, 0); 
    }

};