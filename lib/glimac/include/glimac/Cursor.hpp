#ifndef WORLD_IMAKER_CURSOR_HPP 
#define WORLD_IMAKER_CURSOR_HPP
#pragma once
#include <GL/glew.h>
#include <glimac/Cube.hpp>

namespace glimac {
    class Cursor : public Cube {
        public:
        Cursor();
        ~Cursor() = default;
        void draw();
    }; 
}

#endif