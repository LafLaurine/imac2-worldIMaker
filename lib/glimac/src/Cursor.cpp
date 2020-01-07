#include <glimac/Cursor.hpp>
#include <iostream>

namespace glimac{

    //the cursor needs to be visible even inside cubes, so we disable the depth_test
    void Cursor::draw() {
       glBindVertexArray(m_vao);
       glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
       //red color because why not
       glm::vec4 colorCursor(1.0f,0.0f,0.0f,1.0f);
       setColor(colorCursor);
       glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
       glDisable(GL_DEPTH_TEST);
       glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, 0);
       glEnable(GL_DEPTH_TEST);
       glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
       glBindVertexArray(0);
    }
}