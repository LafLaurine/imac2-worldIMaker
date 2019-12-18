#include <glimac/Cursor.hpp>
#include <iostream>

namespace glimac{

    void Cursor::drawCursor(Cube &cursor) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        cursor.draw();
    }
}