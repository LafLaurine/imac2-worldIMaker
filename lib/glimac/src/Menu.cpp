#include <iostream>
#include <string>
#include <glimac/Menu.hpp>
#include <GL/glew.h>
#include <glimac/gl-exception.hpp>

namespace glimac {
    const VertexTex vertices[] = { 
        VertexTex(glm::vec2(-1.f, 1.f), 
                glm::vec2(0.f, 1.f)),
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

    Menu::Menu(Scene &scene, ProgramType type):m_ibo(0),m_vbo(0),m_vao(0),m_texture(Texture("MenuPrincipal.png")), m_scene(scene), m_type(type)
    {
        scene.loadProgram(type,"../shaders/texture.vs.glsl","../shaders/texture.fs.glsl");
        const GLuint VERTEX_ATTR_POSITION = 0;
        const GLuint VERTEX_ATTR_TEXCOORD = 1;

        GLCall(glGenBuffers(1, &m_vbo));
        GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_vbo)); 
        GLCall(glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(VertexTex), vertices, GL_STATIC_DRAW));
        GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));

        GLCall(glGenBuffers(1, &m_ibo));
        GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo));
        GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6*sizeof(uint32_t), indices, GL_STATIC_DRAW));
        GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));

        GLCall(glGenVertexArrays(1, &m_vao));
        GLCall(glBindVertexArray(m_vao));
        GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo));

        GLCall(glEnableVertexAttribArray(VERTEX_ATTR_POSITION));
        GLCall(glEnableVertexAttribArray(VERTEX_ATTR_TEXCOORD));

        GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_vbo));
        GLCall(glVertexAttribPointer(VERTEX_ATTR_POSITION, 2, GL_FLOAT, GL_FALSE, sizeof(VertexTex), (const GLvoid*) offsetof(VertexTex, position)));
        GLCall(glVertexAttribPointer(VERTEX_ATTR_TEXCOORD, 2, GL_FLOAT, GL_FALSE, sizeof(VertexTex), (const GLvoid*) offsetof(VertexTex, texCoords)));
        GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
        GLCall(glBindVertexArray(0)); 
    }
    
    void Menu::draw(Scene &scene, ProgramType type){
        scene.useProgram(type);
        GLCall(glClear(GL_COLOR_BUFFER_BIT));
		
        GLCall(glUniform1i(glGetUniformLocation(scene.m_programs[type].getGLId(), "uTexure"), m_texture.m_textureId));
        GLCall(glEnable(GL_BLEND));
        GLCall(glBindVertexArray(m_vao));
        GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo));
        GLCall(glActiveTexture(GL_TEXTURE1));
		GLCall(glBindTexture(GL_TEXTURE_2D, m_texture.m_textureId));
        GLCall(glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*) 0, 1));
        GLCall(glActiveTexture(GL_TEXTURE1));
        GLCall(glBindVertexArray(0));
        GLCall(glDisable(GL_BLEND));
    }

};