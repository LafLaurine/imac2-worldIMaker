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
            ///some bool values that check game state
            bool gameOn;
            bool gamePause;
            bool gameLoad;
        public:
            ///default constructor of PlayerController
            PlayerController();
            ///default destructor of PlayerController
            ~PlayerController() = default;
            inline bool getGameOn() const{return gameOn;};
            inline bool getGamePause() const{return gamePause;};
            inline bool setGamePauseF() {return gamePause = false;};
            inline bool setGameOn() {return gameOn = true;};
            inline bool getGameLoad() const{return gameLoad;};
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