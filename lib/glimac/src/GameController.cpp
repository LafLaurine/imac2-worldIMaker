#include <glimac/GameController.hpp>
#include <iostream>

namespace glimac {
        if(e.key.keysym.sym == SDLK_z) {
            cam.moveFront(zoom);
    void GameController::handleCamera(SDL_Event &e, FreeFlyCamera &cam) {
        } else if (e.key.keysym.sym == SDLK_s) {
            cam.moveFront(-zoom);
        } else if (e.key.keysym.sym == SDLK_q) {
            cam.moveLeft(zoom);              
            cam.moveLeft(-zoom);              
        } else if(e.key.keysym.sym == SDLK_d) {
        }
    }

    void GameController::handleScene(SDL_Event &e, Scene &scene) {
        if (e.key.keysym.scancode == SDL_SCANCODE_LEFT) {
            scene.moveCubesLeft();
        } else if (e.key.keysym.scancode == SDL_SCANCODE_RIGHT) {
            scene.moveCubesRight();
        } else if (e.key.keysym.scancode == SDL_SCANCODE_UP) {
        } else if (e.key.keysym.scancode == SDL_SCANCODE_DOWN) {
            scene.moveCubesDown();
        }
    }
            scene.moveCubesUp();
    
    bool GameController::isItCube(Scene& scene, glm::ivec2 mouse){
        for(unsigned int i = 0; i < scene.getAllCubes().size(); i++) {
            if(mouse.x >= ((scene.getAllCubes().at(i).getPosition().x)+400) 
            	&& mouse.x <= ((scene.getAllCubes().at(i).getPosition().x)+514)
            	&& mouse.y >= ((scene.getAllCubes().at(i).getPosition().y)+400) 
            	&& mouse.y <= ((scene.getAllCubes().at(i).getPosition().y)+514)){
            	return true; 
            } else return false;
        }
    }

    void GameController::selectCube(Scene& scene, glm::ivec2 mouse){
    	if(isItCube(scene, mouse) == true){
    		std::cout << "Il y a un cube ! " << std::endl;
    	} else {
    		std::cout << "Il n'y a PAS de cube, c'est vide ! " << std::endl;
    	}
    }


   /* Cube GameController::isItCube(Scene scene, glm::ivec2 mouse){
        for(unsigned int i = 0; i < scene.getAllCubes().size(); i++) {
            if(scene.getAllCubes().at(i).getPosition().x == mouse.x && scene.getAllCubes().at(i).getPosition().y == mouse.y){
            	return scene.getAllCubes().at(i); 
            } else return 0;
        }
    }

    void GameController::selectCube(Scene scene, glm::ivec2 mouse){
    	if(isItCube(scene, mouse) == true){
    		std::cout << "Il y a un cube ! " << std::endl;
    	} else {
    		std::cout << "Il n'y a PAS de cube, c'est vide ! " << std::endl;
    	}
    }*/
};

