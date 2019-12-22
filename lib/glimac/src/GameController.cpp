#include <glimac/GameController.hpp>
#include <iostream>

namespace glimac {

    void GameController::handleCamera(SDL_Event &e, TrackballCamera &cam) {
        if(e.key.keysym.sym == SDLK_z) {
            cam.moveFront(-zoom);
            } else if (e.key.keysym.sym == SDLK_s) {
            cam.moveFront(zoom);
        } else if (e.key.keysym.sym == SDLK_q) {
            cam.rotateLeft(zoom);              
        } else if(e.key.keysym.sym == SDLK_d) {
            cam.rotateLeft(-zoom);            
        }
        else if(e.key.keysym.sym == SDLK_u) {
            cam.rotateUp(-zoom);            
        }

        else if(e.key.keysym.sym == SDLK_w) {
            cam.rotateUp(zoom);            
        }
    }
    
    void GameController::handleScene(SDL_Event &e, Scene &scene, Cursor& cursor) {
        if (e.key.keysym.sym == SDLK_c) {
            
        } else if (e.key.keysym.scancode == SDL_SCANCODE_LEFT) {
            cursor.setPositionX((cursor.getPosition().x)-1);            
            isThereACube(scene, cursor);
        } else if (e.key.keysym.scancode == SDL_SCANCODE_RIGHT) {
           cursor.setPositionX((cursor.getPosition().x)+1);
            isThereACube(scene, cursor);
        } else if (e.key.keysym.scancode == SDL_SCANCODE_UP) {
        	cursor.setPositionY((cursor.getPosition().y)+1);
        	isThereACube(scene, cursor);
        } else if (e.key.keysym.scancode == SDL_SCANCODE_DOWN) {
            cursor.setPositionY((cursor.getPosition().y)-1);
            isThereACube(scene, cursor);
        } else if(e.key.keysym.scancode == SDL_SCANCODE_KP_MINUS){
        	cursor.setPositionZ((cursor.getPosition().z)-1);
        	isThereACube(scene, cursor);
        } else if(e.key.keysym.scancode == SDL_SCANCODE_KP_PLUS){
        	cursor.setPositionZ((cursor.getPosition().z)+1);
        	isThereACube(scene, cursor);
        } else if (e.key.keysym.sym == SDLK_e) {
            extrudeCube(scene,cursor);
        }
        else if (e.key.keysym.sym == SDLK_g) {
            digCube(scene,cursor);
        }
        std::cout << cursor.getPosition() << std::endl;
    }
            
    
    int GameController::getIndexCube(Scene& scene, Cursor& cursor){
        for(unsigned int i = 0; i < scene.getAllCubes().size(); i++) {
            if(cursor.getPosition().x >= ((scene.getAllCubes().at(i).getPosition().x)) 
            	&& cursor.getPosition().x <= ((scene.getAllCubes().at(i).getPosition().x))
            	&& cursor.getPosition().y >= ((scene.getAllCubes().at(i).getPosition().y)) 
            	&& cursor.getPosition().y <= ((scene.getAllCubes().at(i).getPosition().y))
                && cursor.getPosition().z <= ((scene.getAllCubes().at(i).getPosition().z))
                && cursor.getPosition().z >= ((scene.getAllCubes().at(i).getPosition().z))){
            	return  i; 
            }
        }
        return -1; 
    }

    bool GameController::checkPositionCursor(Scene &scene, glm::vec3 position) {
        if (   position.x <= scene.getLength() && position.z <= scene.getWidth()
            && position.x >= 0 && position.z >= 0
            && position.y <= 10 && position.y >= 0) return true;
        else
        {
            std::cerr << "Curseur en dehors du monde" << std::endl;
            return false;
        } 
    }


    bool GameController::isThereACube(Scene& scene, Cursor& cursor){
    	int cubeIndex = getIndexCube(scene,cursor);
    	if(cubeIndex == -1 || !scene.getAllCubes().at(cubeIndex).isVisible()){
    		std::cout << "Il n'y a PAS de cube, c'est vide !  " << std::endl;
            return false;
    	} else {
    		std::cout << "Il y a un cube ! " << std::endl;
            return true;
    	}
    }

    void GameController::addCube(Scene& scene, Cursor& cursor){
            int cubeIndex = getIndexCube(scene,cursor);
            if(isThereACube(scene,cursor)) {
                std::cout << "HE OH TU PEUX PAS AJOUTER DE CUBE Y'EN A DEJA UN !!!" << std::endl;
            }
            else if(cubeIndex != -1){
                scene.getAllCubes().at(cubeIndex).setVisible();
            }
            else {
                std::cout << "en dehors grille" << std::endl;
            }
    }


    int GameController::getHighestCube(Scene &scene, Cursor &cursor)
    {
            int maxCol = scene.getHeight();
            int cubeIndex = getIndexCube(scene,cursor);
            if(checkPositionCursor(scene, cursor.getPosition())) {
                bool cube_found = false;
                while(cursor.getPosition().y<=maxCol && !cube_found) {
                    if(scene.getAllCubes().at(Scene::from1Dto3D(glm::ivec3(cursor.getPosition().x, cursor.getPosition().y, cursor.getPosition().z))).isVisible() ){
                        cube_found = true;
                    }
                    else{
                        cursor.setPositionY((cursor.getPosition().y)+1);
                    }
                }
            }
            std::cout << cubeIndex << std::endl;
            return cubeIndex;
    }

    //retourner position cubeIndex

    void GameController::deleteCube(Scene& scene, Cursor& cursor){
            int cubeIndex = getIndexCube(scene,cursor);
            if(isThereACube(scene,cursor)) {
               scene.getAllCubes().at(cubeIndex).setInvisible();
            }
            else if (cubeIndex == -1) {
                std::cout << "EH OH TU PEUX PAS SUPP DU VIDE" << std::endl;
            }
            else {
                std::cout << "en dehors grille" << std::endl;
            }
    }

    void GameController::extrudeCube(Scene& scene, Cursor &cursor)
    {
        if(isThereACube(scene,cursor))
        {
            int y = getHighestCube(scene,cursor);
            //position heighest cube
            scene.getAllCubes().at(Scene::from1Dto3D(glm::ivec3(cursor.getPosition().x,y+1,cursor.getPosition().z))).setVisible();
            
        }
    }

    void GameController::digCube(Scene& scene, Cursor &cursor)
    {
        if(isThereACube(scene,cursor))
        {
            int y = getHighestCube(scene,cursor);
            scene.getAllCubes().at(y-1).setInvisible();          
        }
    }

    void GameController::changeColorCube(Scene& scene, Cursor &cursor){
        int cubeIndex = getIndexCube(scene,cursor);
        if(isThereACube(scene,cursor)){
            Cube cube = scene.getAllCubes().at(cubeIndex);
            cube.setColor(cube.getColor());
        } else {
            std::cout << "Il n'y a pas de cube" << std::endl;
        }

    }



};