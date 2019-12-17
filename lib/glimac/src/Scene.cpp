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

        MV = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -10.0f));
        ProjMatrix = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 100.0f);
        glm::mat4 viewProjMat = ProjMatrix * MV;

        glUniformMatrix4fv(uViewProjLocation, // Location
                            1, // Count
                            GL_FALSE, // Transpose
                            glm::value_ptr(viewProjMat)); // Value

    }

    void Scene::recalculate_matrices(FreeFlyCamera &camera,Cube cube) {
            glm::mat4 camera_VM = camera.getViewMatrix();
            glm::mat4 modelMat = glm::translate(glm::mat4(1.0f), cube.getPosition());
            glUniformMatrix4fv(uModelLocation, // Location
                            1, // Count
                            GL_FALSE, // Transpose
                            glm::value_ptr(modelMat * camera_VM)); // Value   
    }

    void Scene::initAllCubes(unsigned int nb_cubes) {
        for (unsigned int layer = 0; layer < nb_cubes; layer++) {
            for (unsigned int i= 0; i < nb_cubes; i++)
            {
                for(unsigned int j= 0 ; j<nb_cubes ; j++)
                {
                    Cube temp_cube(glm::vec3(layer,i,j));
                    if(layer > 3) {
                        temp_cube.setInvisible(true);
                    }
                    temp_cube.setPositionX((temp_cube.getPosition().x)-1);
                    temp_cube.setPositionY((temp_cube.getPosition().y)-1);
                    m_all_cubes.emplace_back(temp_cube);
                }
            }
        }
    }

    void Scene::drawCubes(FreeFlyCamera &camera) {
        for(unsigned int i = 0; i < m_all_cubes.size(); i++) {
            recalculate_matrices(camera,m_all_cubes.at(i));
            if(m_all_cubes.at(i).getInvisible() == 0) {
                m_all_cubes.at(i).draw();
            }
        }
    }
 
 /*
    void Scene::moveCubesLeft() {
        for(unsigned int i = 0; i < m_all_cubes.size(); i++) {
            m_all_cubes.at(i).setPositionX((m_all_cubes.at(i).getPosition().x)-1);
        }
    }

    void Scene::moveCubesRight() {
        for(unsigned int i = 0; i < m_all_cubes.size(); i++) {
            m_all_cubes.at(i).setPositionX((m_all_cubes.at(i).getPosition().x)+1);
        }
    }

    void Scene::moveCubesUp() {
        for(unsigned int i = 0; i < m_all_cubes.size(); i++) {
            m_all_cubes.at(i).setPositionY((m_all_cubes.at(i).getPosition().y)+1);
        }
    }


    void Scene::moveCubesDown() {
        for(unsigned int i = 0; i < m_all_cubes.size(); i++) {
            m_all_cubes.at(i).setPositionY((m_all_cubes.at(i).getPosition().y)-1);
        }
    }*/

}