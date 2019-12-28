#ifndef WORLD_IMAKER_CURSOR_HPP 
#define WORLD_IMAKER_CURSOR_HPP
#pragma once
#include <GL/glew.h>
#include <glimac/Cube.hpp>

namespace glimac {
    class Cursor : public Cube {
        public:
        ///default constructor of cursor
        Cursor() = default;
        ///default destructor of cursor
        ~Cursor() = default;
        //draw cursor
        void draw();
    }; 
}

#endif