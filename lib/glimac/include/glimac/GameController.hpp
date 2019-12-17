#ifndef WORLD_IMAKER_GAMECONTROLLER_HPP 
#define WORLD_IMAKER_GAMECONTROLLER_HPP
#pragma once
#include <iostream>
#include <glimac/glm.hpp> 
#include <glimac/Scene.hpp>
#include <glimac/SDLWindowManager.hpp>
#include <SDL2/SDL.h>

namespace glimac {

    class GameController {
        private :
            FreeFlyCamera camera;
        public:
            GameController() = default;
            ~GameController() = default;
            void handleCamera(SDL_Event e, FreeFlyCamera cam);
            bool isItCube(Scene& scene, glm::ivec2 mouse);
            void selectCube(Scene& scene, glm::ivec2 mouse);
    };

}

#endif