#include <glimac/GameController.hpp>
#include <iostream>

namespace glimac {
    void GameController::handleCamera(SDL_Event &e, FreeFlyCamera &cam) {
        if(e.key.keysym.sym == SDLK_z) {
            cam.moveFront(zoom);
        } else if (e.key.keysym.sym == SDLK_s) {
            cam.moveFront(-zoom);
        } else if (e.key.keysym.sym == SDLK_q) {
            cam.moveLeft(zoom);              
        } else if(e.key.keysym.sym == SDLK_d) {
            cam.moveLeft(-zoom);              
        }
    }

    void GameController::handleScene(SDL_Event &e, Scene &scene) {
        if (e.key.keysym.scancode == SDL_SCANCODE_LEFT) {
            scene.moveCubesLeft();
        } else if (e.key.keysym.scancode == SDL_SCANCODE_RIGHT) {
            scene.moveCubesRight();
        } else if (e.key.keysym.scancode == SDL_SCANCODE_UP) {
            scene.moveCubesUp();
        } else if (e.key.keysym.scancode == SDL_SCANCODE_DOWN) {
            scene.moveCubesDown();
        }
    }
};

