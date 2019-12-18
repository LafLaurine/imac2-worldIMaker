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

    Scene::Scene(int height, int width, int len):m_height(height), m_width(width), m_length(len) {

    }

    void Scene::create_uniform_matrices(ProgramType type)
    {
        uModelLocation = glGetUniformLocation(m_programs[type].getGLId(), "uModel");
        std::cout << "value uModelLocation : " << uModelLocation << "id program used uModelLocation : " << m_programs[type].getGLId() << std::endl;
        uViewProjLocation = glGetUniformLocation(m_programs[type].getGLId(), "uViewProj");
        uNormalMatLocation = glGetUniformLocation(m_programs[type].getGLId(), "uNormalMat");
        std::cout << "value uViewProjLocation : " << uViewProjLocation << "id program used uViewProjLocation : " << m_programs[type].getGLId() << std::endl;
        
        glm::mat4 modelMat = glm::mat4(1.0f);

        glUniformMatrix4fv(uModelLocation, // Location
                            1, // Count
                            GL_FALSE, // Transpose
                            glm::value_ptr(modelMat)); // Value

        MVMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -10.0f));
        ProjMatrix = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 100.0f);
        glm::mat4 viewProjMat = ProjMatrix * MVMatrix;
        glm::mat4 normalMat = glm::transpose(glm::inverse(MVMatrix));

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
            glm::mat4 camera_VM = camera.getViewMatrix();
            glm::mat4 modelMat = glm::translate(glm::mat4(1.0f), cube.getPosition());
            glUniformMatrix4fv(uModelLocation, // Location
                            1, // Count
                            GL_FALSE, // Transpose
                            glm::value_ptr(modelMat * camera_VM)); // Value   
    }

    void Scene::initAllCubes() {
        for (int width = 0; width < this->m_width; width++) {
            for (int length = 0; length < this->m_length; length++)
            {
                for(int i= 0 ; i<3 ; i++)
                {
                    Cube temp_cube(glm::vec3(width,length,i));
                    
                    temp_cube.setVisible();
                    temp_cube.setPositionX((temp_cube.getPosition().x)-1);
                    temp_cube.setPositionY((temp_cube.getPosition().y)-1);
                    temp_cube.setPositionZ((temp_cube.getPosition().z)-1);
                    this->m_all_cubes.push_back(temp_cube);
                }
                for(int k = 3 ; k < this->m_height ; k++){
                    Cube temp_cube(glm::vec3(width,length,k));

                    temp_cube.setPositionX((temp_cube.getPosition().x)-1);
                    temp_cube.setPositionY((temp_cube.getPosition().y)-1);
                    temp_cube.setPositionZ((temp_cube.getPosition().z)-1);
                    this->m_all_cubes.push_back(temp_cube);
                }
            }
        }
    }

    void Scene::drawCubes(FreeFlyCamera &camera) {
        for(int i = 0 ; i < this->m_width ; i++ ){
            for(int j = 0 ; j < this->m_length ; j++){
                for(int k = 0 ; k < this->m_height ; k++){
                    recalculate_matrices(camera,m_all_cubes.at(i));
                    if(!this->m_all_cubes.at(i).isVisible()) {
                        this->m_all_cubes.at(i).draw();
                    }
                }
            }
        }
    }

}