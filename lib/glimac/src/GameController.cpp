#include <glimac/GameController.hpp>
#include <iostream>

namespace glimac {

    GameController::GameController(Scene *scene, Cursor *cursor): zoom(1.0f), m_scene(scene), m_cursor(cursor), m_currentCube(nullptr) {
    }
    /*
    GameController::GameController(Scene &scene, Cursor &cursor): zoom(1.0f), m_scene(&scene), m_cursor(&cursor), m_currentCube(nullptr) {
    }*/

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
            
    
    /*int GameController::getIndexCube(Scene& scene, Cursor& cursor){
        //parse the scene cubes
        for(unsigned int i = 0; i < scene.getAllCubes().size(); i++) {
            //check if cursor is at the same position as a cube
            if(cursor.getPosition() == (scene.getAllCubes().at(i).getPosition())){
            	return  i; 
            }
        }
        //if there is no cube, return -1
        return -1; 
    }*/



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

   /* void GameController::addCube(Scene& scene, Cursor& cursor){
        // Cube's pointer
        Cube* cubePtr;
        //check if cursor is in the scene
        if(checkPositionCursor(scene, cursor.getPosition())) {
            //check if there is already a cube
            if(isThereACube(scene,cursor)) {
                std::cout << "You CANNOT add a cube, there is one already" << std::endl;
            }
            //if not, set the cube visible and add the cube to the multi-dimensional array
            else{
                cubePtr = scene.tabCubes[cursor.getPosition().x][cursor.getPosition().y][cursor.getPosition().z];
                cubePtr->setVisible();
            }
        }
    }*/

        //tempCube détruit, initialiser dans pushBack et récuperer plutot m.all_cube.back() pour mettre dan tabCubes[][][]
    void GameController::initAllCubes() {
        //initialize all the cube of the scene
        for (unsigned int z = 0; z < m_scene->getLength(); z++) {
                for(unsigned int x= 0 ; x<m_scene->getWidth() ; x++)
                {
                    Cube cube(glm::ivec3(x,0,z));
                    m_scene->getAllCubes().push_back(cube);
                    m_scene->tabCubes[x][0][z] = &m_scene->getAllCubes().back();
                }
        }
    }

    void GameController::drawCubes(TrackballCamera &camera,GLuint texId) {
        //for each cube, calculate matrice and if it is visible, draw it
        for(Cube& cube : m_scene->getAllCubes()){
            m_scene->recalculateMatrices(camera,cube);
            cube.draw(texId);
        }
    }

    // Add cube to vector and array
    void GameController::addCube(Cube cube){
        //if(this->isThereACube()) {
            std::cout << "You CANNOT add a cube, there is one already" << std::endl;
        //} else {
            std::cout << "Add cube" << std::endl;
            //cube.setVisible();
            m_scene->getAllCubes().push_back(cube);
            m_scene->tabCubes[cube.getPosition().x][cube.getPosition().y][cube.getPosition().z] = &m_scene->getAllCubes().back();
        //}
    }

    // Delete cube to vector and array
    void GameController::deleteCube(Cube* cube){
        if(this->isThereACube()) {
            //cube->setInvisible();
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
    void GameController::addToCursor(){
        this->checkCurrentCube();
        if(!this->checkCurrentCube()){
            this->addCube(Cube(m_cursor->getPosition()));
            this->checkCurrentCube();
        } else {
            std::cout << "Cube already visible" << std::endl;
        }
    }

    // Delete cube with cursor's position
    void GameController::deleteToCursor(){
        this->checkCurrentCube();
        if(m_currentCube == nullptr){
            std::cout << "No cube here !" << std::endl;
        } else {
            this->deleteCube(m_currentCube);
            this->checkCurrentCube();
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
        Cube* lastCubeFound;
        m_currentCube = m_scene->tabCubes[m_cursor->getPosition().x][20][m_cursor->getPosition().z];
        this->updateCursorPosition(glm::ivec3(m_cursor->getPosition().x,20,m_cursor->getPosition().z));
        glm::ivec3 newPosCursor;

        for(int i=m_scene->getHeight() ; i=1 ; i--){
            if(!this->checkCurrentCube()){
                this->updateCursorPosition(glm::ivec3(m_cursor->getPosition().x,i,m_cursor->getPosition().z));
                m_currentCube = m_scene->tabCubes[m_cursor->getPosition().x][i][m_cursor->getPosition().z];
            } else {
                lastCubeFound = m_scene->tabCubes[m_currentCube->getPosition().x][m_currentCube->getPosition().y][m_currentCube->getPosition().z];
                std::cout << "Pos last cube found : " << lastCubeFound->getPosition() << std::endl;
                newPosCursor = {lastCubeFound->getPosition().x, (lastCubeFound->getPosition().y)+1, lastCubeFound->getPosition().z};
                std::cout << "newPosCursor : " << newPosCursor << std::endl;
                this->updateCursorPosition(newPosCursor);
                this->addToCursor();
                // add properties of lastCubeFound to the new cube
            }

            // if no cube found, add one on the ground
            if(!isThereACube()){
                newPosCursor = {lastCubeFound->getPosition().x, 0, lastCubeFound->getPosition().z};
                this->updateCursorPosition(newPosCursor);
                this->addToCursor();
            }
        }

    }


    // Dig
    void GameController::digCube(){
        Cube* lastCubeFound;
        m_currentCube = m_scene->tabCubes[m_cursor->getPosition().x][20][m_cursor->getPosition().z];
        glm::ivec3 newPosCursor;

        for(int i=m_scene->getHeight() ; i=1 ; --i){
            if(m_currentCube == nullptr){
                m_currentCube = m_scene->tabCubes[m_cursor->getPosition().x][i][m_cursor->getPosition().z];
            } else {
                lastCubeFound = m_scene->tabCubes[m_currentCube->getPosition().x][m_currentCube->getPosition().y][m_currentCube->getPosition().z];
                this->updateCursorPosition(lastCubeFound->getPosition());
                this->deleteToCursor();
            }

            // if cube found, delete one on the ground
            if(isThereACube()){
                newPosCursor = {lastCubeFound->getPosition().x, 0, lastCubeFound->getPosition().z};
                this->updateCursorPosition(newPosCursor);
                this->deleteToCursor();
            }
        }

    }


    /*
   OK - quand on construit l'objet, il faut récupérer en attribut un pointeur sur la scene et un pointeur sur le curseur (constructeur)
   OK - dans constructeur Gamecontroller, il faut un pointeur sur un cube qui stockera le cube actuellement sélectionné
        quand on bouge curseur, fait action sur cube séléctionné on regarde le cube
    - methode degré 1 :
   OK     - ADDCUBE() : ajouter un cube prend en argument un cube et s'occupe d'ajouter le cube au système (vecteur + tableau de positions) on regarde le cube et sa position et on rentre dans le tableau
   OK     Verification à faire pour voi si il y deja un cuvbe
   OK     - DELETECUBE() : supprimer cube. prend un pointeur sur cube. elle retire le cube du vecteur et retire le cube du tableau.
   OK     - CHECKCURRENTCUBE() : actualiser CheckCurrentCUbe().  Ne prend rien en argument et regarde quel est le cube qui est à l'endroit ou est le curseur. Utilise le tableau avec la position du curseur
   OK     retourne le pointeur sur le cube ou nullptr. si pointeyr existe on le met dans l'attribut *Cube
    - methode de degre 2 :
   OK     - ADDTOCURSOR() : ajouter depuis le sélecteur. prend rien en argument. Regarde si dans l'attribut CurrentCube si c'est vide ou il y a un ptr. Si vide c'est bon, si il y a ptr s'arrete. 
   OK     Crée un nveau cube et lui donne la position du curseur. Ajoute le cube (utiliser la méthode). actualise la sélection (méthode à use). 
   OK     - DELETETOCURSOR() : supprimer depuis le selecteur. rien en argument. doit enlever le cube ou le selecteur est. Doit se servir des methode de degre 1.
   OK       - move selector. En argument : un vec3 (soit en relatif (deplacement) ou absolu(donne pos d'arrivee)). Va prendre la position et l'ajoute à la pos du curseur actuelle( deplacement) ou donne la nvelle pos au curseur
   OK       on appelle CheckCurrentCUbe(). 
    -methode de degre 3 :
   OK     - extrude. rien en argument. Récupere la pos du curseur et identifier le Y. Lance une boucle qui va demander ce qu'il y a dans le tableau 3D à la case qui se trouve avec le meme x et z que le curseur
   OK         on commence a prendre y = 20 ( le plus haut dans le monde), on regarde cette case, on consulte le tableau et si il y a un cube dans la case on arrete la boucle
   OK         si pas de cube dans la case, descendre y de 1 avec le i de la boucle. iterer la boucle jusqu'au sol si besoin. Il faut stocker l'endroit ou la boucle s'est arretée. 
   OK         (** ce qui est mieux c'est de stocker le ptr sur le cube récupéré)
            Si on a un cube : (**on peut récuperer la couleur le cube d'en dessous et mettre le nveau cube de la meme couleur, memes proporietes)
   OK             creer un cube, donne position de la position du cube à la fin de la boucle +1 dans les y
   OK             appelle méthode de degre 2 : moveSelector(). Prendre la méthode qui permet de lui donner une nouvelle position et lui dire que le selecteur aille à la position du cube qu'on vient de créer
   OK         Si pas de cube : ptr = nullptr . Ajoute un cube au niveau du sol. Pournous niveau +1 ou pas. recupere x et z du curseur, creer un cube avec ce x et z et en y prend 0 ou 1 en fonction.
   OK             Bouger le selecteur ou est le cube.
   OK     -dig. parcoure la colonne en fontion du curseur et boucle va se lancer jusqu'à arriver sur un cube. 
   OK         Si un cube : déplacer le curseur : moveselector(), passe position du cube en argument qu'on a trouvée avec la boucle
   OK             deleteCube(cubePtr).
   OK         Si pas de cube : En fonction de si on veut pas detruire le sol voir au niveau de la boucle pour pas y acceder.
   OK             bouger le curseur. moveSelector(), garde son x et z, le y devient 0 ou 1 en fonction de ce qu'on veut
    CLEANER LES FONCTIONS ET ENLEVER LES SECNE ET CURSOR EN ARGUMENT
    */



    /*void GameController::deleteCube(Scene& scene, Cursor& cursor){
        //get index of the cube where the cursor is
        Cube* cubePtr = scene.tabCubes[cursor.getPosition().x][cursor.getPosition().y][cursor.getPosition().z];
        //check if cursor is in the scene
        if(checkPositionCursor(scene, cursor.getPosition())) {
            //check if there is a cube
            if(isThereACube(scene,cursor)) {
            //set cube invisible
            cubePtr->setInvisible();
            cubePtr = nullptr;
            //set color of the cube to the original one, because if we add it again, we don't want to keep the color change
            glm::vec3 color(0.6f,0.2f,0.2f);
            cubePtr->setColor(color);
            }
            else if (cubePtr == nullptr) {
                std::cout << "You cannot erase emptiness..." << std::endl;
            }
        }
    }

    Cube* GameController::getHighestCube(Scene &scene, Cursor &cursor)
    {
        int maxCol = scene.getHeight();
        int counter = maxCol;
        // take a pointer on the higher possible cube in the column 
        Cube* cubePtr = scene.tabCubes[cursor.getPosition().x][maxCol][cursor.getPosition().z];
        // check if cursor is in the scene
        if(checkPositionCursor(scene, cursor.getPosition())) {
            bool cube_found = false;
            while(cursor.getPosition().y<=maxCol && !cube_found) {
                std::cout << " rentre dans fonction" << std::endl;
                 cubePtr = scene.tabCubes[cursor.getPosition().x][counter][cursor.getPosition().z];
                 counter -= 1;
                // if the cube corresponding to the cubeIndex is visible
                if(cubePtr->isVisible()){
                    std::cout << "cube visible" << std::endl;
                    cube_found = true;
                }
                else if(!cubePtr->isVisible()){
                    // else check in position y+1
                    std::cout << "no cube visible in this position" << std::endl;
                    cursor.setPositionY((cursor.getPosition().y)-1);
                }
            }
        }
            // return highest cube index
            return cubePtr;

        //int maxCol = scene.getHeight();
        int cubeIndex = getIndexCube(scene, cursor);

        if(checkPositionCursor(scene, cursor.getPosition())) {
            if(scene.getAllCubes().at(cubeIndex).isVisible()){
                // position du curseur Y+1 et on recheck
                int posY = scene.getAllCubes().at(cubeIndex).getPosition().y;
                // take the y+1 position
                int posYPlusOne = posY+1;
                cursor.setPositionY(posYPlusOne);
                //cubeIndex = getIndexCube(scene, cursor);
                std::cout << "CUBE VISIBLE +1" << std::endl;

            } else{
                // retourne position du curseur Y-1
                int posY = scene.getAllCubes().at(cubeIndex).getPosition().y;
                // take the y+1 position
                int posYMinusOne = posY-1;
                cursor.setPositionY(posYMinusOne);
                cubeIndex = getIndexCube(scene, cursor);
                std::cout << "CUBE PAS VISIBLE - 1" << std::endl;
            }
        }
        return cubeIndex;
    }

    void GameController::extrudeCube(Scene& scene, Cursor &cursor)
    {
        if(isThereACube(scene,cursor))
        {
            /// pointer on the highest cube of the column
            Cube* highestCube = getHighestCube(scene,cursor);
            // y of highest cube
            int posY = highestCube->getPosition().y;
            // take the y+1 position
            int posYPlusOne = posY+1;
            // and put the cursor in this position to find the cube index associated
            cursor.setPositionY(posYPlusOne);
            Cube* highestCubePlusOne = scene.tabCubes[cursor.getPosition().x][posYPlusOne][cursor.getPosition().z];
            std::cout << "pointer on the highest cube + 1 : " << highestCubePlusOne << std::endl;
            // make it visible
            highestCubePlusOne->setVisible();
            scene.tabCubes[highestCubePlusOne->getPosition().x][highestCubePlusOne->getPosition().y][highestCubePlusOne->getPosition().z] = highestCubePlusOne;
        } else {
            std::cout << "else" << std::endl;
            Cube* highestCube = getHighestCube(scene, cursor);
            highestCube->setVisible();
            scene.tabCubes[highestCube->getPosition().x][highestCube->getPosition().y][highestCube->getPosition().z] = highestCube;
        }
    }

    void GameController::digCube(Scene& scene, Cursor &cursor)
    {
        if(isThereACube(scene,cursor))
        {
            //int y = getHighestCube(scene,cursor);
            //scene.getAllCubes().at(y-1).setInvisible();  

            Cube* highestCube = getHighestCube(scene,cursor);
            highestCube->setInvisible();
            scene.tabCubes[highestCube->getPosition().x][highestCube->getPosition().y][highestCube->getPosition().z] = nullptr;
        }
    }*/

    void GameController::changeColorCube(Overlay &overlay, TrackballCamera &camera){
        //get pointer on the cube where the cursor is
        Cube* cubePtr = m_scene->tabCubes[m_cursor->getPosition().x][m_cursor->getPosition().y][m_cursor->getPosition().z];
        //check if there is a cube
        if(this->isThereACube()){
            //get color from the overlay color picker
            glm::vec3 color = glm::make_vec3(overlay.getColor());
            //change color of the cube selected
            cubePtr->setColor(color);
        } else {
            std::cout << "There is no cube" << std::endl;
        }
    }

    void GameController::setTextureCube(Texture &tex) {
        //get index of the cube where the cursor is
        ////int cubeIndex = getIndexCube(scene,cursor);
        Cube* cubePtr = m_scene->tabCubes[m_cursor->getPosition().x][m_cursor->getPosition().y][m_cursor->getPosition().z];
        std::cout << cubePtr << std::endl;
        cubePtr->m_type = 1;
        if(this->isThereACube()){
            tex.initTexture(*m_scene);
        } else {
            std::cout << "There is no cube" << std::endl;
        }
    }

    void GameController::cleanScene(std::list <Cube> &allCubes)
    {
        //set invisible all the cube
        for(Cube &c: allCubes){
            c.setInvisible();
        }
    }


};