#include <glimac/Scene.hpp>

namespace glimac{

	void Scene::displayScene() {
		overlay.beginFrame(windowManager.m_window);
		cube.initCube(); 
        glm::mat4 globalMVMatrix =  camera.getViewMatrix();
       
        //move cube
        glm::mat4 modelMat = glm::translate(glm::mat4(1.0f), cube.getPosition());
        glUniformMatrix4fv(uMVLocation, // Location
                        1, // Count
                        GL_FALSE, // Transpose
                        glm::value_ptr(modelMat * globalMVMatrix));
        
		overlay.drawOverlay();
        cube.draw();
        overlay.endFrame(windowManager.m_window);
	}
}