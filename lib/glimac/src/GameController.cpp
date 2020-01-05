#include <glimac/GameController.hpp>
#include <iostream>

namespace glimac {


    GameController::GameController(Scene *scene, Cursor *cursor): zoom(1.0f), m_scene(scene), m_cursor(cursor), m_currentCube(nullptr) {
    }

    GameController::GameController() {
        gameOn = false;
        gameLoad = false;
        gamePause = false;
    }

    void GameController::inGame() {
        if(gameOn == false) {
            gameOn = true;
        }
    }


    void GameController::loadGame() {
        if(gameLoad == false) {
            gameLoad = true;
            inGame();
        }
    }

    void GameController::pausedGame() {
        if(gamePause == false) {
            gamePause = true;
        }
    }
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
    
    void GameController::handleScene(SDL_Event &e, Overlay &overlay, TrackballCamera &camera) {
        const Uint8 *state = SDL_GetKeyboardState(NULL);
        // handle key for scene : holding C and moving cursor for painting
        if (state[SDL_SCANCODE_C]) {
            if (e.key.keysym.scancode == SDL_SCANCODE_LEFT)
                m_cursor->setPositionX((m_cursor->getPosition().x)-1);   
            else if (e.key.keysym.scancode == SDL_SCANCODE_RIGHT)
                m_cursor->setPositionX((m_cursor->getPosition().x)+1);
            else if (e.key.keysym.scancode == SDL_SCANCODE_UP)
        	    m_cursor->setPositionY((m_cursor->getPosition().y)+1);   
            else if (e.key.keysym.scancode == SDL_SCANCODE_DOWN)
                m_cursor->setPositionY((m_cursor->getPosition().y)-1);
            changeColorCube(overlay,camera);
        }
        //left arrow to move cursor to the left + check if there is a cube
        else if (e.key.keysym.scancode == SDL_SCANCODE_LEFT) {
            m_cursor->setPositionX((m_cursor->getPosition().x)-1);            
            isThereACube();
        //right arrow to move cursor to the left + check if there is a cube
        } else if (e.key.keysym.scancode == SDL_SCANCODE_RIGHT) {
           m_cursor->setPositionX((m_cursor->getPosition().x)+1);
            isThereACube();
        //up arrow to move cursor to the left + check if there is a cube
        } else if (e.key.keysym.scancode == SDL_SCANCODE_UP) {
        	m_cursor->setPositionY((m_cursor->getPosition().y)+1);
        	isThereACube();
        //down arrow to move cursor to the left + check if there is a cube
        } else if (e.key.keysym.scancode == SDL_SCANCODE_DOWN) {
            m_cursor->setPositionY((m_cursor->getPosition().y)-1);
            isThereACube();
        //- to move cursor to the back + check if there is a cube
        } else if(e.key.keysym.scancode == SDL_SCANCODE_KP_MINUS){
        	m_cursor->setPositionZ((m_cursor->getPosition().z)-1);
        	isThereACube();
        //+ move cursor to the front + check if there is a cube
        } else if(e.key.keysym.scancode == SDL_SCANCODE_KP_PLUS){
        	m_cursor->setPositionZ((m_cursor->getPosition().z)+1);
        	isThereACube();
        // e to extrude cube
        } else if (e.key.keysym.sym == SDLK_e) {
            extrudeCube();
        }
        //g to dig cube
        else if (e.key.keysym.sym == SDLK_g) {
            digCube();
        }
        std::cout << m_cursor->getPosition() << std::endl;
    }
            
    bool GameController::checkPositionCursor(glm::ivec3 position) {
        //check if cursor is in the scene (height, width and length check)
        if (position.x <= m_scene->getLength() && position.z <= m_scene->getWidth()
            && position.x >= 0 && position.z >= 0
            && position.y <= m_scene->getHeight() && position.y >= 0) return true;
        else
        {
            std::cerr << "Cursor out of the world" << std::endl;
            return false;
        } 
    }

    bool GameController::isThereACube(){
    	//////int cubeIndex = getIndexCube(scene,cursor);
        Cube* cubePtr = m_scene->tabCubes[m_cursor->getPosition().x][m_cursor->getPosition().y][m_cursor->getPosition().z];
        //if cube's pointer is null or that the cube is invisible, then there is no cube
    	if(cubePtr == nullptr){
    		std::cout << "There is NO cube, it's empty !  " << std::endl;
            return false;
    	} else {
    		std::cout << "There is a cube ! " << std::endl;
            return true;
    	}
    }

    void GameController::initAllCubes() {
        //initialize all the cube of the scene
        for (int z = 0; z < m_scene->getLength(); z++) {
            for(int x= 0 ; x< m_scene->getWidth() ; x++)
            {
                Cube cube(glm::ivec3(x,0,z));
                m_scene->getAllCubes().push_back(cube);
                m_scene->tabCubes[x][0][z] = &m_scene->getAllCubes().back();
            }
        }
    }

    void GameController::drawCubes(TrackballCamera &camera,Texture &tex) {
        //for each cube, calculate matrice and if it is visible, draw it
        for(Cube& cube : m_scene->getAllCubes()){
            m_scene->recalculateMatrices(camera,cube);
            cube.draw(tex.getId());
        }
    }

    // Add cube to vector and array
    void GameController::addCube(Cube cube){
        std::cout << "You CANNOT add a cube, there is one already" << std::endl;
        m_scene->getAllCubes().push_back(cube);
        m_scene->tabCubes[cube.getPosition().x][cube.getPosition().y][cube.getPosition().z] = &m_scene->getAllCubes().back();
    }

    // Delete cube to vector and array
    void GameController::deleteCube(Cube* cube){
        if(this->isThereACube()) {
            m_scene->getAllCubes().remove(*cube);
            m_scene->tabCubes[cube->getPosition().x][cube->getPosition().y][cube->getPosition().z] = nullptr;
        } else {
            std::cout << "You cannot erase emptiness..." << std::endl;
        }
    }

    // Update current cube, check which cube is in the cursor's position
    bool GameController::checkCurrentCube(){
        if(this->isThereACube()) {
            m_currentCube = m_scene->tabCubes[m_cursor->getPosition().x][m_cursor->getPosition().y][m_cursor->getPosition().z];
            return true;
        } else {
            std::cout << "There is no cube to check" << std::endl;
            return false;
        }
    }

    // Add cube with cursor's position
    bool GameController::addToCursor(){
        this->checkCurrentCube();
        if(!this->checkCurrentCube()){
            this->addCube(Cube(m_cursor->getPosition()));
            this->checkCurrentCube();
            return true;
        } else {
            std::cout << "Cube already visible" << std::endl;
            return false;
        }
    }

    // Delete cube with cursor's position
    bool GameController::deleteToCursor(){
        this->checkCurrentCube();
        if(m_currentCube == nullptr){
            std::cout << "No cube here !" << std::endl;
            return false;
        } else {
            this->deleteCube(m_currentCube);
            this->checkCurrentCube();
            return true;
        }
    }

    // Move cursor
    void GameController::moveCursor(glm::ivec3 position){
        if(checkPositionCursor(m_cursor->getPosition())) {
            m_cursor->setPosition(m_cursor->getPosition() += position); 
            this->checkCurrentCube();
        }
    }

    // Replace the cursor's position with a new
    void GameController::updateCursorPosition(glm::ivec3 newPosition){
        if(checkPositionCursor(m_cursor->getPosition())) {
            m_cursor->setPosition(newPosition);
            this->checkCurrentCube();
        }
    }

    // Extrude
    void GameController::extrudeCube(){
        Cube* lastCubeFound = nullptr;
        lastCubeFound = m_scene->tabCubes[m_cursor->getPosition().x][m_scene->getHeight()][m_cursor->getPosition().z];
         std::cout << "Last cube fround : " << lastCubeFound << std::endl;

        for(int i=m_scene->getHeight() ; i=1 ; --i){
            if(lastCubeFound==nullptr){
                lastCubeFound = m_scene->tabCubes[m_cursor->getPosition().x][i][m_cursor->getPosition().z];
                std::cout << "pos last cube : " << lastCubeFound->getPosition() << std::endl;
            } else {
                this->updateCursorPosition(glm::ivec3(lastCubeFound->getPosition().x, (lastCubeFound->getPosition().y)+1, lastCubeFound->getPosition().z));
                std::cout << "pos last cube else : " << lastCubeFound->getPosition() << std::endl;
                this->addToCursor();
                break;
            }
        }
        // if no cube found, add one on the ground
        if(!isThereACube()){
            this->updateCursorPosition(glm::ivec3(m_cursor->getPosition().x,0,m_cursor->getPosition().z));
            this->addToCursor();
        }
    }

    // Dig
    void GameController::digCube(){
        Cube* lastCubeFound;
        m_currentCube = m_scene->tabCubes[m_cursor->getPosition().x][20][m_cursor->getPosition().z];

        for(int i = m_scene->getHeight(); i = 1 ; --i){
            if(lastCubeFound == nullptr){
                lastCubeFound = m_scene->tabCubes[m_cursor->getPosition().x][i][m_cursor->getPosition().z];
            } else {
                lastCubeFound = m_scene->tabCubes[m_currentCube->getPosition().x][m_currentCube->getPosition().y][m_currentCube->getPosition().z];
                this->updateCursorPosition(lastCubeFound->getPosition());
                this->deleteToCursor();
                break;
            }  
        }
        // if cube found, delete one on the ground
        if(isThereACube()){
            this->updateCursorPosition(glm::ivec3(m_cursor->getPosition().x,0,m_cursor->getPosition().z));
            this->deleteToCursor();
        }

    }

    void GameController::changeColorCube(Overlay &overlay, TrackballCamera &camera){
        //get pointer on the cube where the cursor is
        Cube* cubePtr = m_scene->tabCubes[m_cursor->getPosition().x][m_cursor->getPosition().y][m_cursor->getPosition().z];
        //check if there is a cube
        if(this->isThereACube()){
            //get color from the overlay color picker
            glm::vec4* color = overlay.getColor();
            //change color of the cube selected
            cubePtr->setColor(*color);

        } else {
            std::cout << "There is no cube for changing color" << std::endl;
        }
    }

    void GameController::setTextureCube(Texture &tex) {
        //find the cube where the cursor is
        Cube* cubePtr = m_scene->tabCubes[m_cursor->getPosition().x][m_cursor->getPosition().y][m_cursor->getPosition().z];
        std::cout << cubePtr << std::endl;
        if(this->isThereACube()){
            cubePtr->m_type = 1;
        } else {
            std::cout << "There is no cube" << std::endl;
        }
    }

    void GameController::cleanScene(std::list <Cube> &allCubes)
    {
        allCubes = std::list<Cube>();
        for (int z = 0; z < m_scene->getLength() ; z++) {
            for(int x= 0 ; x <m_scene->getWidth() ; x++) {
                for(int y= 1 ; y < m_scene->getHeight() ; y++) {
                    allCubes.remove(*m_scene->tabCubes[x][y][z]);
                    m_scene->tabCubes[x][y][z] = nullptr;

                }
            }
        }
    }

};