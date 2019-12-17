#ifndef WORLD_IMAKER_GAMECONTROLLER_HPP 
#define WORLD_IMAKER_GAMECONTROLLER_HPP
#pragma once
#include <glimac/glm.hpp> 
#include <glimac/Scene.hpp>
#include <SDL2/SDL.h>

namespace glimac {

    class GameController {
        private :
            float zoom = 0.1f;
        public:
            GameController() = default;
            ~GameController() = default;
            void handleCamera(SDL_Event &e, FreeFlyCamera &cam);
            void handleScene(SDL_Event &e, Scene &scene);
            void handleEvents(SDL_Event &e);
    };

}

#endif