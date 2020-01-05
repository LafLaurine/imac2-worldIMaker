#ifndef GLIMAC_MENU
#define GLIMAC_MENU

#include <iostream>
#include <string>
#include <GL/glew.h>
#include <glimac/Scene.hpp>
#include <glimac/Texture.hpp>

namespace glimac
{

struct VertexTex{
    glm::vec2 position;
    glm::vec2 texCoords;

    VertexTex(){
        this->position.x = 0;
        this->position.y = 0;
        this->texCoords.x = 0;
        this->texCoords.y = 0;
    }

    VertexTex(glm::vec2 position, glm::vec2 texCoords)
    : position(position),
        texCoords(texCoords)
    {
    }
};

    class Menu{
        private:
            GLuint m_ibo;
            GLuint m_vbo;
            GLuint m_vao;
            Texture* m_texture;
            Scene &m_scene;
            ProgramType m_type;
        public :
            Menu() = default;
            Menu(Scene &scene, ProgramType type,std::string tex);
            ~Menu() = default;
            void draw(Scene &scene, ProgramType type);
            
    };
    bool floatIsBetween(const float value, const int min, const int max);
};

#endif