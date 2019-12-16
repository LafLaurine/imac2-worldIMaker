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

    void Scene::create_uniform_matrices(ProgramType type)
    {
        uModelLocation = glGetUniformLocation(m_programs[type].getGLId(), "uModel");
        uViewProjLocation = glGetUniformLocation(m_programs[type].getGLId(), "uViewProj");
        glm::mat4 modelMat = glm::mat4(1.0f);

        glUniformMatrix4fv(uModelLocation, // Location
                            1, // Count
                            GL_FALSE, // Transpose
                            glm::value_ptr(modelMat)); // Value

        glm::mat4 viewMat = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -10.0f));
        glm::mat4 projMat = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 100.0f);
        glm::mat4 viewProjMat = projMat * viewMat;

        glUniformMatrix4fv(uViewProjLocation, // Location
                            1, // Count
                            GL_FALSE, // Transpose
                            glm::value_ptr(viewProjMat)); // Value

    }

    void Scene::recalculate_matrices(FreeFlyCamera camera, Cube cube) {
        glm::mat4 camera_VM = camera.getViewMatrix();
        glm::mat4 modelMat = glm::translate(glm::mat4(1.0f), cube.getPosition());
        glUniformMatrix4fv(uModelLocation, // Location
                        1, // Count
                        GL_FALSE, // Transpose
                        glm::value_ptr(modelMat * camera_VM)); // Value
    }
/*
    void Scene::initAllCubes(unsigned int nb_cubes) {
        for (unsigned int i=0; i<nb_cubes; i++)
        {
            m_all_cubes.push_back(Cube());
        }
    }

    void Scene::displayScene(ProgramType type) 
    {
        for(long unsigned int i = 0; i < m_all_cubes.size(); i++)
        {
            loadScene(type);
            std::cout << m_all_cubes[i].getPosition() << std::endl;
        }
    }

    void Scene::drawCubes(ProgramType cubeType) {
        for(long unsigned int i = 0; i < m_all_cubes.size(); i++) {
            m_cubes[cubeType].draw();
        }
    }*/
}