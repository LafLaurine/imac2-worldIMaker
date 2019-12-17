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
            cam.moveLeft(-zoom);              
        } else if(e.key.keysym.sym == SDLK_d) {
        }
    }

    void GameController::handleScene(SDL_Event &e, Scene &scene, FreeFlyCamera &cam) {
    	glm::vec3 position = cam.getCamPosition();
        if (e.key.keysym.scancode == SDL_SCANCODE_LEFT) {
            scene.moveCubesLeft();
            selectCube(scene, position);
        } else if (e.key.keysym.scancode == SDL_SCANCODE_RIGHT) {
            scene.moveCubesRight();
            selectCube(scene, position);
        } else if (e.key.keysym.scancode == SDL_SCANCODE_UP) {
        	scene.moveCubesUp();
        	selectCube(scene, position);
        } else if (e.key.keysym.scancode == SDL_SCANCODE_DOWN) {
            scene.moveCubesDown();
            selectCube(scene, position);
        }
    }
            
    
    Cube* GameController::isItCube(Scene& scene, glm::vec3 position){
        for(unsigned int i = 0; i < scene.getAllCubes().size(); i++) {
            if(position.x >= ((scene.getAllCubes().at(i).getPosition().x)-0.5) 
            	&& position.x <= ((scene.getAllCubes().at(i).getPosition().x)+0.5)
            	&& position.y >= ((scene.getAllCubes().at(i).getPosition().y)-0.5) 
            	&& position.y <= ((scene.getAllCubes().at(i).getPosition().y)+0.5)){
            	return &(scene.getAllCubes().at(i)); 
            }
        } 
        return nullptr;
    }

    void GameController::selectCube(Scene& scene, glm::vec3 position){
    	Cube* cubeSelected = isItCube(scene, position);
    	if(cubeSelected != nullptr){
    		std::cout << "Il y a un cube ! " << std::endl;
    	} else {
    		std::cout << "Il n'y a PAS de cube, c'est vide ! " << std::endl;
    	}
    }
};


/*Cube* GameController::isItCube(Scene& scene, glm::vec3 position){
        for(unsigned int i = 0; i < scene.getAllCubes().size(); i++) {
            if(mouse.x >= ((scene.getAllCubes().at(i).getPosition().x)+400) 
            	&& mouse.x <= ((scene.getAllCubes().at(i).getPosition().x)+514)
            	&& mouse.y >= ((scene.getAllCubes().at(i).getPosition().y)+400) 
            	&& mouse.y <= ((scene.getAllCubes().at(i).getPosition().y)+514)){
            	return &(scene.getAllCubes().at(i)); 
            }
        } 
        return nullptr;
    }*/
