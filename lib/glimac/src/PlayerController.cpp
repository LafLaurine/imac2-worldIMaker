#include <glimac/PlayerController.hpp>
#include <iostream>

namespace glimac {

    PlayerController::PlayerController() {
        gameOn = false;
        gameLoad = false;
        gamePause = false;
    }

    void PlayerController::inGame() {
        if(gameOn == false) {
            gameOn = true;
        }
    }


    void PlayerController::loadGame() {
        if(gameLoad == false) {
            gameLoad = true;
            inGame();
        }
    }

    void PlayerController::pausedGame() {
        if(gamePause == false) {
            gamePause = true;
        }
    }

    void PlayerController::handleCamera(SDL_Event &e, TrackballCamera &cam) {
            //handle key for camera : Z and S for zoom
            if(e.key.keysym.sym == SDLK_z) {
                cam.moveFront(-zoom);
            } else if (e.key.keysym.sym == SDLK_s) {
                cam.moveFront(zoom);
            // q and d for moving left/right
            } else if (e.key.keysym.sym == SDLK_q) {
                cam.rotateLeft(-zoom);              
            } else if(e.key.keysym.sym == SDLK_d) {
                cam.rotateLeft(zoom);            
            }
            //u and w for rotate up/down
            else if(e.key.keysym.sym == SDLK_u) {
                cam.rotateUp(-zoom);            
            }
            else if(e.key.keysym.sym == SDLK_w) {
                cam.rotateUp(zoom);            
            }
            // 0, 1 and 2 for posing the camera at different places
            else if(e.key.keysym.scancode == SDL_SCANCODE_0) {
                cam.posBottom();
            }
            else if(e.key.keysym.scancode == SDL_SCANCODE_1) {
                cam.posDefault();
            }
            else if(e.key.keysym.scancode == SDL_SCANCODE_2) {
                cam.posLeft();
            }
        }

};