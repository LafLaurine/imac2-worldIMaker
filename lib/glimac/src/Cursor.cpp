#include <glimac/Cursor.hpp>
#include <iostream>

namespace glimac{

    void Cursor::draw() {
       glBindVertexArray(m_vao);
       glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
       glDrawElements(GL_LINES, 36, GL_UNSIGNED_SHORT, (void*) 0);
       glBindVertexArray(0);
    }
}