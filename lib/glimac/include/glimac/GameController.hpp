#ifndef WORLD_IMAKER_GAMECONTROLLER_HPP 
#define WORLD_IMAKER_GAMECONTROLLER_HPP
#pragma once
#include <iostream>
#include <glimac/glm.hpp> 
#include <glimac/Cursor.hpp>
#include <glimac/Scene.hpp>
#include <SDL2/SDL.h>


namespace glimac {

    class GameController {
        private :
            float zoom = 1.0f;
            glm::vec3 m_position;
        public:
            GameController() = default;
            ~GameController() = default;
            void handleCamera(SDL_Event &e, TrackballCamera &cam);
            void handleScene(SDL_Event &e, Scene &scene, Cursor &cursor);
            void handleEvents(SDL_Event &e);
            int getIndexCube(Scene& scene, Cursor &cursor);
            bool isThereACube(Scene& scene, Cursor &cursor);
            inline glm::vec3 getPosition(){return m_position;};
            void addCube(Scene& scene, Cursor& cursor);
            void deleteCube(Scene& scene, Cursor& cursor);
            unsigned int checkHeighestCube(Scene &scene, Cursor &cursor);
            void extrudeCube(Scene &scene, Cursor &cursor);
            void digCube(Scene &scene, Cursor &cursor);
            bool checkPositionCursor(Scene &scene, glm::vec3 position);
            int getHighestCube(Scene &scene, Cursor &cursor);
    };

}

#endif