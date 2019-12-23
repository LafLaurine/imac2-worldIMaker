#include <glimac/Cursor.hpp>
#include <iostream>

namespace glimac{

    void Cursor::draw() {
       glBindVertexArray(m_vao);
       glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
       glm::vec3 colorCursor(1.0f,0.0f,0.0f);
       setColor(colorCursor);
       glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
       glDisable(GL_DEPTH_TEST);
       glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, 0);
       glEnable(GL_DEPTH_TEST);
       glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
       glBindVertexArray(0);
    }
}