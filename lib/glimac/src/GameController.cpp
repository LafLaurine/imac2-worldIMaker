#include <glimac/GameController.hpp>
#include <iostream>

namespace glimac {

    void GameController::handleCamera(SDL_Event &e, TrackballCamera &cam) {
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
    
    void GameController::handleScene(SDL_Event &e, Scene &scene, Cursor& cursor, Overlay &overlay, TrackballCamera &camera) {
        const Uint8 *state = SDL_GetKeyboardState(NULL);
        // handle key for scene : holding C and moving cursor for painting
        if (state[SDL_SCANCODE_C]) {
            if (e.key.keysym.scancode == SDL_SCANCODE_LEFT)
                cursor.setPositionX((cursor.getPosition().x)-1);   
            else if (e.key.keysym.scancode == SDL_SCANCODE_RIGHT)
                cursor.setPositionX((cursor.getPosition().x)+1);
            else if (e.key.keysym.scancode == SDL_SCANCODE_UP)
        	    cursor.setPositionY((cursor.getPosition().y)+1);   
            else if (e.key.keysym.scancode == SDL_SCANCODE_DOWN)
                cursor.setPositionY((cursor.getPosition().y)-1);
            changeColorCube(scene,cursor,overlay,camera);
        }
        //left arrow to move cursor to the left + check if there is a cube
        else if (e.key.keysym.scancode == SDL_SCANCODE_LEFT) {
            cursor.setPositionX((cursor.getPosition().x)-1);            
            isThereACube(scene, cursor);
        //right arrow to move cursor to the left + check if there is a cube
        } else if (e.key.keysym.scancode == SDL_SCANCODE_RIGHT) {
           cursor.setPositionX((cursor.getPosition().x)+1);
            isThereACube(scene, cursor);
        //up arrow to move cursor to the left + check if there is a cube
        } else if (e.key.keysym.scancode == SDL_SCANCODE_UP) {
        	cursor.setPositionY((cursor.getPosition().y)+1);
        	isThereACube(scene, cursor);
        //down arrow to move cursor to the left + check if there is a cube
        } else if (e.key.keysym.scancode == SDL_SCANCODE_DOWN) {
            cursor.setPositionY((cursor.getPosition().y)-1);
            isThereACube(scene, cursor);
        //- to move cursor to the back + check if there is a cube
        } else if(e.key.keysym.scancode == SDL_SCANCODE_KP_MINUS){
        	cursor.setPositionZ((cursor.getPosition().z)-1);
        	isThereACube(scene, cursor);
        //+ move cursor to the front + check if there is a cube
        } else if(e.key.keysym.scancode == SDL_SCANCODE_KP_PLUS){
        	cursor.setPositionZ((cursor.getPosition().z)+1);
        	isThereACube(scene, cursor);
        // e to extrude cube
        } else if (e.key.keysym.sym == SDLK_e) {
            extrudeCube(scene,cursor);
        }
        //g to dig cube
        else if (e.key.keysym.sym == SDLK_g) {
            digCube(scene,cursor);
        }
        std::cout << cursor.getPosition() << std::endl;
    }
            
    
    int GameController::getIndexCube(Scene& scene, Cursor& cursor){
        //parse the scene cubes
        for(unsigned int i = 0; i < scene.getAllCubes().size(); i++) {
            //check if cursor is at the same position as a cube
            if(cursor.getPosition() == (scene.getAllCubes().at(i).getPosition())){
            	return  i; 
            }
        }
        //if there is no cube, return -1
        return -1; 
    }

    bool GameController::checkPositionCursor(Scene &scene, glm::vec3 position) {
        //check if cursor is in the scene (height, width and length check)
        if (position.x <= scene.getLength() && position.z <= scene.getWidth()
            && position.x >= 0 && position.z >= 0
            && position.y <= scene.getHeight() && position.y >= 0) return true;
        else
        {
            std::cerr << "Cursor out of the world" << std::endl;
            return false;
        } 
    }

    bool GameController::isThereACube(Scene& scene, Cursor& cursor){
        //get index of the cube where the cursor is
    	int cubeIndex = getIndexCube(scene,cursor);
        //if index is -1 or that the cube is invisible, then there is no cube
    	if(cubeIndex == -1 || !scene.getAllCubes().at(cubeIndex).isVisible()){
    		std::cout << "There is NO cube, it's empty !  " << std::endl;
            return false;
    	} else {
    		std::cout << "There is a cube ! " << std::endl;
            return true;
    	}
    }

    void GameController::addCube(Scene& scene, Cursor& cursor){
        //get index of the cube where the cursor is
        int cubeIndex = getIndexCube(scene,cursor);
        //check if cursor is in the scene
        if(checkPositionCursor(scene, cursor.getPosition())) {
            //check if there is already a cube
            if(isThereACube(scene,cursor)) {
                std::cout << "You CANNOT add a cube, there is one already" << std::endl;
            }
            //if not, set the cube visible
            else if(cubeIndex != -1){
                scene.getAllCubes().at(cubeIndex).setVisible();
            }
        }
    }

    void GameController::deleteCube(Scene& scene, Cursor& cursor){
        //get index of the cube where the cursor is
        int cubeIndex = getIndexCube(scene,cursor);
        //check if cursor is in the scene
        if(checkPositionCursor(scene, cursor.getPosition())) {
            //check if there is a cube
            if(isThereACube(scene,cursor)) {
            //set cube invisible
            scene.getAllCubes().at(cubeIndex).setInvisible();
            //set color of the cube to the original one, because if we add it again, we don't want to keep the color change
            glm::vec3 color(0.6f,0.2f,0.2f);
            scene.getAllCubes().at(cubeIndex).setColor(color);
            }
            else if (cubeIndex == -1) {
                std::cout << "You cannot erase emptiness..." << std::endl;
            }
        }
    }

    int GameController::getHighestCube(Scene &scene, Cursor &cursor)
    {
        int maxCol = scene.getHeight();
        int cubeIndex;
        // check if cursor is in the scene
        if(checkPositionCursor(scene, cursor.getPosition())) {
            bool cube_found = false;
            while(cursor.getPosition().y<=maxCol && !cube_found) {
                // if the cube corrsponding to the cubeIndex is visible
                if(scene.getAllCubes().at(getIndexCube(scene,cursor)).isVisible()){
                    cubeIndex = getIndexCube(scene,cursor);
                    cube_found = true;
                }
                else{
                    // else check in position y+1
                    std::cout << "no cube visible in this position" << std::endl;
                    cursor.setPositionY((cursor.getPosition().y)+1);
                }
            }
        }
            // return highest cube index
            return cubeIndex;
    }

    void GameController::extrudeCube(Scene& scene, Cursor &cursor)
    {
        if(isThereACube(scene,cursor))
        {
            /// index of highest cube
            int highestCube = getHighestCube(scene,cursor);
        
            // y of highest cube
            int posY = scene.getAllCubes().at(highestCube).getPosition().y;
            int posYPlusOne = posY+1;
            cursor.setPositionY(posYPlusOne);
            int highestCubePlusOne = getIndexCube(scene, cursor);
            std::cout << "index highest cube + 1 : " << highestCubePlusOne << std::endl;
            scene.getAllCubes().at(highestCubePlusOne).setVisible();
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

    void GameController::changeColorCube(Scene& scene, Cursor &cursor, Overlay &overlay, TrackballCamera &camera){
        //get index of the cube where the cursor is
        int cubeIndex = getIndexCube(scene,cursor);
        //check if there is a cube
        if(isThereACube(scene,cursor)){
            //get color from the overlay color picker
            glm::vec3 color =  glm::make_vec3(overlay.getColor());
            //change color of the cube selected
            scene.getAllCubes().at(cubeIndex).setColor(color);
        } else {
            std::cout << "There is no cube" << std::endl;
        }
    }

    void GameController::setTextureCube(Scene &scene, Cursor &cursor, Texture &tex) {
        //get index of the cube where the cursor is
        int cubeIndex = getIndexCube(scene,cursor);
        std::cout << cubeIndex << std::endl;
        scene.getAllCubes().at(cubeIndex).m_type = 1;
        if(isThereACube(scene,cursor)){
            tex.initTexture(scene);
        } else {
            std::cout << "There is no cube" << std::endl;
        }
    }

    void GameController::cleanScene(std::vector <Cube> &allCubes)
    {
        //set invisible all the cube
        for(Cube &c: allCubes){
            c.setInvisible();
        }
    }


};