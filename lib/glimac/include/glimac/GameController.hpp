#ifndef WORLD_IMAKER_GAMECONTROLLER_HPP 
#define WORLD_IMAKER_GAMECONTROLLER_HPP
#pragma once
#include <iostream>
#include <glimac/glm.hpp> 
#include <glimac/Cursor.hpp>
#include <glimac/Scene.hpp>
#include <glimac/Overlay.hpp>
#include <list>
#include <algorithm>
#include <glimac/Texture.hpp>

namespace glimac {
    
    class GameController {
        private :
            Scene* m_scene;
            Cursor* m_cursor;
            Cube* m_currentCube;
        public:
            ///default constructor of GameController
            GameController();
            //constructor of GameController
            GameController(Scene *scene, Cursor *cursor);
            ///default destructor of GameController
            ~GameController() = default;
            ///handle scene movements
            void handleScene(SDL_Event &e, Overlay &overlay, FreeFlyCamera &camera);
            ///check if there is a cube at cursor
            bool isThereACube();
            ///initialize default scene
            void initAllCubes();
            ///draw cubes to the scene
            void drawCubes(FreeFlyCamera &camera, Texture &tex);
            ///add cube to the scene
            void addCube(Cube cube);
            ///delete cube of the scene
            void deleteCube(Cube* cube);
            /// check the current cube associated to the cursor's position
            bool checkCurrentCube();
            /// Add cube with cursor's position
            bool addToCursor();
            /// Delete cube with cursor's position
            bool deleteToCursor();
            /// Move cursor
            void moveCursor(glm::ivec3 position);
            /// Repalce the cursor's position with a new
            void updateCursorPosition(glm::ivec3 newPosition);
            ///extrude cube where the cursor is
            void extrudeCube();
            ///dig cube where the cursor is
            void digCube();
            ///check if cursor is in the scene
            bool checkPositionCursor(glm::ivec3 position);
            ///clean scene
            void cleanScene(std::list <Cube> &allCubes);
            ///change color of the cube selected
            void changeColorCube(Overlay &overlay);
            ///set texture of the cube selected
            void setTextureCube(Texture &tex);
            ///remove texture of the cube selected
            void removeTextureCube(Texture &tex);
    };

}

#endif