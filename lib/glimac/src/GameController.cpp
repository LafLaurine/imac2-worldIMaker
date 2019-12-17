#include <glimac/GameController.hpp>

namespace glimac {
    void GameController::handleCamera(SDL_Event e, FreeFlyCamera cam) {

    }
    
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

