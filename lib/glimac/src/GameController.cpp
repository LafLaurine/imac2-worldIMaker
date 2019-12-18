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
    
    void GameController::handleScene(SDL_Event &e, Scene &scene, Cube& cursor) {
        if (e.key.keysym.scancode == SDL_SCANCODE_LEFT) {
            cursor.setPositionX((cursor.getPosition().x)-1);            
            selectCube(scene, cursor);
        } else if (e.key.keysym.scancode == SDL_SCANCODE_RIGHT) {
           cursor.setPositionX((cursor.getPosition().x)+1);
            selectCube(scene, cursor);
        } else if (e.key.keysym.scancode == SDL_SCANCODE_UP) {
        	cursor.setPositionY((cursor.getPosition().y)+1);
        	selectCube(scene, cursor);
        } else if (e.key.keysym.scancode == SDL_SCANCODE_DOWN) {
            cursor.setPositionY((cursor.getPosition().y)-1);
            selectCube(scene, cursor);
        } else if(e.key.keysym.scancode == SDL_SCANCODE_KP_MINUS){
        	cursor.setPositionZ((cursor.getPosition().z)-1);
        	selectCube(scene, cursor);
        } else if(e.key.keysym.scancode == SDL_SCANCODE_KP_PLUS){
        	cursor.setPositionZ((cursor.getPosition().z)+1);
        	selectCube(scene, cursor);
        }
    }
            
    
    Cube* GameController::isItCube(Scene& scene, Cube& cursor){
        for(unsigned int i = 0; i < scene.getAllCubes().size(); i++) {
            if(cursor.getPosition().x >= ((scene.getAllCubes().at(i).getPosition().x)) 
            	&& cursor.getPosition().x <= ((scene.getAllCubes().at(i).getPosition().x))
            	&& cursor.getPosition().y >= ((scene.getAllCubes().at(i).getPosition().y)) 
            	&& cursor.getPosition().y <= ((scene.getAllCubes().at(i).getPosition().y))){
            	return &(scene.getAllCubes().at(i)); 
            }
        } 
        return nullptr;
    }

    void GameController::selectCube(Scene& scene, Cube& cursor){
    	Cube* cubeSelected = isItCube(scene, cursor);
    	if(cubeSelected != nullptr){
    		std::cout << "Il y a un cube ! " << std::endl;
    	} else {
    		std::cout << "Il n'y a PAS de cube, c'est vide ! " << std::endl;
    	}
    }

    void GameController::addCube(Scene& scene, Cube& cursor){
            if(isItCube(scene,cursor)) {
                std::cout << "HE OH TU PEUX PAS AJOUTER DE CUBE Y'EN A DEJA UN !!!" << std::endl;
            }
            else {
                std::cout << "Taille avant ajout cube : " << scene.getAllCubes().size() << std::endl;
                cursor.setVisible();
                std::cout << "Taille après ajout cube : " << scene.getAllCubes().size() << std::endl;
            }
    }

    void GameController::deleteCube(Scene& scene, Cube& cursor){
        for(unsigned int i = 0; i < scene.getAllCubes().size(); i++) {
            if(isItCube(scene,cursor)) {
                if(cursor.isVisible()) {
                    cursor.m_visible = false;
                }
            }
            else {
                std::cout << "HE OH TU PEUX PAS SUPPRIMER DU VIDE !!!" << std::endl;
            }
        }
    }
};