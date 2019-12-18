#include <glimac/Scene.hpp>
#include <iostream>

#include <glimac/gl-exception.hpp>

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
        std::cout << "value uModelLocation : " << uModelLocation << "id program used uModelLocation : " << m_programs[type].getGLId() << std::endl;
        uViewProjLocation = glGetUniformLocation(m_programs[type].getGLId(), "uViewProj");
        uNormalMatLocation = glGetUniformLocation(m_programs[type].getGLId(), "uNormalMat");
        std::cout << "value uViewProjLocation : " << uViewProjLocation << "id program used uViewProjLocation : " << m_programs[type].getGLId() << std::endl;
        glm::mat4 modelMat = glm::mat4(1.0f);

        uViewProjLocation = glGetUniformLocation(m_programs[type].getGLId(), "uMVPMatrix");
        if(uViewProjLocation == -1)
            break_assert(false);

        MV = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -10.0f));
        ProjMatrix = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 100.0f);
        glm::mat4 viewProjMat = ProjMatrix * MV;
        glm::mat4 normalMat = glm::transpose(glm::inverse(MV));

        glUniformMatrix4fv(uViewProjLocation, // Location
                            1, // Count
                            GL_FALSE, // Transpose
                            glm::value_ptr(viewProjMat)); // Value

        glUniformMatrix4fv(uNormalMatLocation, // Location
                    1, // Count
                    GL_FALSE, // Transpose
                    glm::value_ptr(normalMat)); // Value

    }

    void Scene::recalculate_matrices(FreeFlyCamera &camera,Cube cube) {
            GLCall(glBindVertexArray(cube.getVAO()));
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cube.getIBO());
            glm::mat4 camera_VM = camera.getViewMatrix();
            glm::mat4 cubeMVMatrix = glm::translate(camera_VM, cube.getPosition()*glm::vec3(2,2,2));
            
           /* glBindTexture(GL_TEXTURE_2D, cube.texId);
            glUniform1i(uTexLocation, 0);*/
            glUniformMatrix4fv(uModelLocation, 1, GL_FALSE, glm::value_ptr(cubeMVMatrix));
            glUniformMatrix4fv(uViewProjLocation, 1, GL_FALSE, glm::value_ptr(ProjMatrix * cubeMVMatrix));
            glUniformMatrix4fv(uNormalLocation, 1, GL_FALSE, glm::value_ptr(NormalMatrix));
    }

    void Scene::initAllCubes(unsigned int nb_cubes) {
        for (unsigned int layer = 0; layer < nb_cubes; layer++) {
            for (unsigned int i= 0; i < nb_cubes; i++)
            {
                for(unsigned int j= 0 ; j<nb_cubes ; j++)
                {
                    Cube temp_cube(glm::vec3(i,layer,j));
                    if(layer > 2) {
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
            if(!m_all_cubes.at(i).getInvisible()) {
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