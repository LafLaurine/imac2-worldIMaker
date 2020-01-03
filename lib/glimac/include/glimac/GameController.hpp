#ifndef WORLD_IMAKER_GAMECONTROLLER_HPP 
#define WORLD_IMAKER_GAMECONTROLLER_HPP
#pragma once
#include <iostream>
#include <glimac/glm.hpp> 
#include <glimac/Cursor.hpp>
#include <glimac/Scene.hpp>
#include <glimac/Overlay.hpp>
#include <glimac/Texture.hpp>
namespace glimac {

    class GameController {
        private :
            float zoom = 1.0f;
        public:
            ///default constructor of GameController
            GameController();
            bool gameOn;
            bool gamePause;
            bool gameLoad;
            ///default destructor of GameController
            ~GameController() = default;
            //if in game
            void inGame();
            void pausedGame();
            void loadGame();
            ///handle camera movements
            void handleCamera(SDL_Event &e, TrackballCamera &cam);
            ///handle scene movements
            void handleScene(SDL_Event &e, Scene &scene, Cursor &cursor, Overlay &overlay, TrackballCamera &camera);
            ///handle SDL event
            void handleEvents(SDL_Event &e);
            ///get index of the cube where the cursor is
            int getIndexCube(Scene& scene, Cursor &cursor);
            ///check if there is a cube at the cursor position
            bool isThereACube(Scene& scene, Cursor &cursor);
            ///add cube to the scene where the cursor is
            bool addCube(Scene& scene, Cursor& cursor);
            ///delete cube of the scene where the cursor is
            bool deleteCube(Scene& scene, Cursor& cursor);
            ///extrude cube where the cursor is
            void extrudeCube(Scene &scene, Cursor &cursor);
            ///dig cube where the cursor is
            void digCube(Scene &scene, Cursor &cursor);
            ///check if cursor is in the scene
            bool checkPositionCursor(Scene &scene, glm::vec3 position);
            ///get heighest cube of the column where the cursor is
            int getHighestCube(Scene &scene, Cursor &cursor);
            ///clean scene
            void cleanScene(std::vector <Cube> &allCubes);
            ///change color of the cube selected
            void changeColorCube(Scene& scene, Cursor &cursor, Overlay &overlay, TrackballCamera &camera);
            ///set texture of the cube selected
            void setTextureCube(Scene &scene, Cursor &cursor, Texture &tex, ProgramType type);
            //remove texture of the cube selected
            void removeTextureCube(Scene &scene, Cursor &cursor, Texture &tex);
    };

}

#endif