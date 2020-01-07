#ifndef GLIMAC_MENU
#define GLIMAC_MENU

#include <iostream>
#include <string>
#include <GL/glew.h>
#include <glimac/Scene.hpp>
#include <glimac/Texture.hpp>

namespace glimac
{   
    ///structure of vertex for menu
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

    class Menu {
        private:
            GLuint m_ibo;
            GLuint m_vbo;
            GLuint m_vao;
            Texture* m_texture;
            Scene &m_scene;
            ProgramType m_type;
        public :
            ///menu constructor by default
            Menu() = default;
            ///menu constructor with specific arguments : scene, type of program and name of the texture
            Menu(Scene &scene,ProgramType type,std::string tex);
            ///menu destructor by default
            ~Menu() = default;
            ///draw menu
            void draw(Scene &scene, ProgramType type);
            
    };
    ///check if there is a float at mouse between some max and min value
    bool floatIsBetween(const float value, const int min, const int max);
};

#endif