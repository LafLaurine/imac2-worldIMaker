#include <glimac/Cursor.hpp>
#include <iostream>

namespace glimac{

    void Cursor::drawCursor() {
        glDrawElements(GL_LINES, 36, GL_UNSIGNED_SHORT, (void*) 0);
    }
}