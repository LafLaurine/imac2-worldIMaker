#ifndef WORLD_IMAKER_PlayerController_HPP 
#define WORLD_IMAKER_PlayerController_HPP
#pragma once
#include <iostream>
#include <glimac/glm.hpp> 
#include <glimac/FreeFlyCamera.hpp>
#include <SDL2/SDL.h>
#include <list>
namespace glimac {

    class PlayerController {
        private :
            float zoom = 1.0f;
        public:
            ///default constructor of PlayerController
            PlayerController();
            ///some bool values that check game state
            bool gameOn;
            bool gamePause;
            bool gameLoad;
            ///default destructor of PlayerController
            ~PlayerController() = default;
            ///if in game
            void inGame();
            ///if game is paused
            void pausedGame();
            ///if game is loaded
            void loadGame();
            ///handle camera movements
            void handleCamera(SDL_Event &e, FreeFlyCamera &cam);
    };

}

#endif