#ifndef WORLD_IMAKER_PlayerController_HPP 
#define WORLD_IMAKER_PlayerController_HPP
#pragma once
#include <iostream>
#include <glimac/glm.hpp> 
#include <glimac/TrackballCamera.hpp>
#include <SDL2/SDL.h>
#include <list>
namespace glimac {

    class PlayerController {
        private :
            float zoom = 1.0f;
        public:
            ///default constructor of PlayerController
            PlayerController();
            //PlayerController(Scene &scene, Cursor &cursor);
            bool gameOn;
            bool gamePause;
            bool gameLoad;

            ///default destructor of PlayerController
            ~PlayerController() = default;
            //if in game
            void inGame();
            void pausedGame();
            void loadGame();
            ///handle camera movements
            void handleCamera(SDL_Event &e, TrackballCamera &cam);
    };

}

#endif