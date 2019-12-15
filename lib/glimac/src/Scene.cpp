#include <glimac/Scene.hpp>
#include <iostream>

namespace glimac{
    void Scene::loadProgram(ProgramType type, std::string vertexShader, std::string fragmentShader) {
        m_programs.emplace(type, glimac::loadProgram(vertexShader,fragmentShader));
        //appel des cubes utilisant le type
	}

	void Scene::useProgram(ProgramType type) {
		m_programs[type].use();
	}

    void Scene::loadScene(ProgramType type)
    {
        uMVPLocation = glGetUniformLocation(m_programs[type].getGLId(), "uMVPMatrix");
        uMVLocation = glGetUniformLocation(m_programs[type].getGLId(), "uMVMatrix");
        uNormalLocation = glGetUniformLocation(m_programs[type].getGLId(), "uNormalMatrix");
    }

    void Scene::initAllCubes(unsigned int nb_cubes) {
        for (unsigned int i=0; i<nb_cubes; i++)
        {
            m_all_cubes.push_back(Cube(glm::vec3(1.0f,float(i),0.0f), glm::vec3(1.0f,0.0f,0.0f)));
        }
    }

    void Scene::displayScene(ProgramType type) 
    {
        for(long unsigned int i = 0; i < m_all_cubes.size(); i++)
        {
            loadScene(type);
            glm::mat4 modelMat = glm::mat4(1.0f);
            glm::mat4 viewMat = glm::translate(glm::mat4(), glm::vec3(0.0f, 0.0f, -5.0f));
            glm::mat4 projMat = glm::perspective(glm::radians(45.0f), (float) 900.0f / 900.0f, 0.1f, 100.0f);
            glm::mat4 normalMatrix = glm::transpose(glm::inverse(viewMat));
            glUniformMatrix4fv(uMVLocation, 1, GL_FALSE, glm::value_ptr(modelMat));
            glUniformMatrix4fv(uMVPLocation, 1, GL_FALSE, glm::value_ptr(projMat * viewMat));
            glUniformMatrix4fv(uNormalLocation, 1, GL_FALSE, glm::value_ptr(normalMatrix));
            std::cout << m_all_cubes[i].getPosition() << std::endl;
        }
    }

    void Scene::moveCube(ProgramType cubeType) {
        for(long unsigned int i = 0; i < m_all_cubes.size(); i++) {
            glm::mat4 modelMat = glm::translate(glm::mat4(1.0f), m_cubes[cubeType].getPosition());
            glm::mat4 globalMVMatrix = camera.getViewMatrix();
            glUniformMatrix4fv(uMVLocation, 1, GL_FALSE, glm::value_ptr(modelMat * globalMVMatrix));
            glBindVertexArray(m_cubes[cubeType].getVAO());
        }
        
    }

    void Scene::drawCube(ProgramType cubeType) {
        for(long unsigned int i = 0; i < m_all_cubes.size(); i++) {
            m_cubes[cubeType].draw();
        }
    }
}