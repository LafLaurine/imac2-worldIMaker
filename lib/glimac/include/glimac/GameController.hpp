#ifndef WORLD_IMAKER_GAMECONTROLLER_HPP 
#define WORLD_IMAKER_GAMECONTROLLER_HPP
#pragma once
#include <iostream>
#include <glimac/glm.hpp> 
#include <glimac/Scene.hpp>
#include <SDL2/SDL.h>


namespace glimac {

    class GameController {
        private :
            float zoom = 0.1f;
            glm::vec3 m_position;
        public:
            GameController() = default;
            ~GameController() = default;
            void handleCamera(SDL_Event &e, FreeFlyCamera &cam);
            void handleScene(SDL_Event &e, Scene &scene, Cube &cursor);
            void handleEvents(SDL_Event &e);
            Cube* isItCube(Scene& scene, Cube &cursor);
            void selectCube(Scene& scene, Cube &cursor);
            inline glm::vec3 getPosition(){return m_position;};
            void addCube(Scene& scene, Cube& cursor);
            void deleteCube(Scene& scene, Cube& cursor);
    };

}

#endif