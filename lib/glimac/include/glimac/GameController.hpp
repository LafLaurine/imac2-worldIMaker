#ifndef WORLD_IMAKER_GAMECONTROLLER_HPP 
#define WORLD_IMAKER_GAMECONTROLLER_HPP
#pragma once
#include <iostream>
#include <glimac/glm.hpp> 
#include <glimac/Cursor.hpp>
#include <glimac/Scene.hpp>
#include <glimac/Overlay.hpp>
#include <glimac/Texture.hpp>
#include <SDL2/SDL.h>


namespace glimac {

    class GameController {
        private :
            float zoom = 1.0f;
            Cursor* m_cursor;
            Scene* m_scene;
            Cube* m_currentCube;
        public:
            ///default constructor of GameController
            GameController() = default;
            //constructor of GameController
            GameController(Scene *scene, Cursor *cursor);
            //GameController(Scene &scene, Cursor &cursor);
            ///default destructor of GameController
            ~GameController() = default;
            ///handle camera movements
            void handleCamera(SDL_Event &e, TrackballCamera &cam);
            ///handle scene movements
            void handleScene(SDL_Event &e, Overlay &overlay, TrackballCamera &camera);
            ///handle SDL event
            //void handleEvents(SDL_Event &e);
            ///get index of the cube where the cursor is
            //int getIndexCube(Scene& scene, Cursor &cursor);
            ///check if there is a cube at the cursor position
            bool isThereACube();
            ///add cube to the scene
            //void addCube(Scene& scene, Cursor& cursor);
            void addCube(Cube cube);
            ///delete cube of the scene
            void deleteCube(Cube* cube);
            /// check the current cube associated to the cursor's position
            Cube* checkCurrentCube();
            /// Add cube with cursor's position
            void addToCursor();
            /// Delete cube with cursor's position
            void deleteToCursor();
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
            ///get heighest cube of the column where the cursor is
            //Cube* getHighestCube(Scene &scene, Cursor &cursor);
            ///clean scene
            void cleanScene(std::vector <Cube> &allCubes);
            ///change color of the cube selected
            void changeColorCube(Overlay &overlay, TrackballCamera &camera);
            ///set texture of the cube selected
            void setTextureCube(Texture &tex);
    };

}

#endif