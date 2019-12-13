#include <glimac/Scene.hpp>

namespace glimac{
    void Scene::loadProgram(ProgramType type, std::string vertexShader, std::string fragmentShader) {
        m_programs.emplace(type, glimac::loadProgram(vertexShader,fragmentShader));
        //appel des cubes utilisant le type
	}

	void Scene::useProgram(ProgramType type) {
		m_programs[type].use();
	}

    void Scene::loadTexture(ProgramType type)
    {
        uMVPLocation = glGetUniformLocation(m_programs[type].getGLId(), "uMVPMatrix");
        uMVLocation = glGetUniformLocation(m_programs[type].getGLId(), "uMVMatrix");
        glm::mat4 modelMat = glm::mat4(1.0f);

        glUniformMatrix4fv(uMVLocation, // Location
                            1, // Count
                            GL_FALSE, // Transpose
                            glm::value_ptr(modelMat)); // Value

        glm::mat4 viewMat = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -10.0f));
        glm::mat4 projMat = glm::perspective(glm::radians(45.0f), (float) 900.0f / 900.0f, 0.1f, 100.0f);
        glm::mat4 viewProjMat = projMat * viewMat;
        

        glUniformMatrix4fv(uMVPLocation, // Location
                            1, // Count
                            GL_FALSE, // Transpose
                            glm::value_ptr(viewProjMat)); // Value
    }
}