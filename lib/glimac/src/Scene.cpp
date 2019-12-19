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

    Scene::Scene(unsigned int height, unsigned int width, unsigned int len):m_height(height), m_width(width), m_length(len) {

    }

    void Scene::create_uniform_matrices(ProgramType type)
    {
        uMVLocation = glGetUniformLocation(m_programs[type].getGLId(), "uModel");
        std::cout << "value uModelLocation : " << uMVLocation << "id program used uModelLocation : " << m_programs[type].getGLId() << std::endl;
        uMVPLocation = glGetUniformLocation(m_programs[type].getGLId(), "uViewProj");
        uNormalMatLocation = glGetUniformLocation(m_programs[type].getGLId(), "uNormalMat");
        uShininess = glGetUniformLocation(m_programs[type].getGLId(), "uShininess");
        uKd = glGetUniformLocation(m_programs[type].getGLId(), "uKd");
        uKs = glGetUniformLocation(m_programs[type].getGLId(), "uKs");
        uLightIntensity = glGetUniformLocation(m_programs[type].getGLId(), "uLightIntensity");
        uLightPosLocation = glGetUniformLocation(m_programs[type].getGLId(), "lightPos");
        std::cout << "value uViewProjLocation : " << uMVPLocation << "id program used uViewProjLocation : " << m_programs[type].getGLId() << std::endl;
        
        glm::mat4 modelMat = glm::mat4(1.0f);

        glUniformMatrix4fv(uMVLocation, // Location
                            1, // Count
                            GL_FALSE, // Transpose
                            glm::value_ptr(modelMat)); // Value

        MVMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -10.0f));
        ProjMatrix = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 100.0f);
        glm::mat4 viewProjMat = ProjMatrix * MVMatrix;
        glm::mat4 normalMat = glm::transpose(glm::inverse(MVMatrix));

        glUniformMatrix4fv(uMVPLocation, // Location
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
            glm::vec4 lightDir4 =  glm::vec4(1.0f, 1.0f, 1.0f, 0.0f);
            lightDir4 = lightDir4 * globalMVMatrix;
            glm::vec3 lightPos = glm::vec3(lightDir4.x, lightDir4.y, lightDir4.z);

            glUniform1f(uShininess, 20.0f);
            // uKd
            glUniform3fv(uKd,1, glm::value_ptr(glm::vec3(0.4f, 0.4f, 0.4f)));
            // uKs
            glUniform3fv(uKs,1, glm::value_ptr(glm::vec3(0.4f, 0.4f, 0.4f)));
            // uLightDir_vs
            glUniform3fv(uLightLocation, 1, glm::value_ptr(lightPos));
            // uLightIntensity
            float earthLi = 5.f;
            glUniform3fv(uLightIntensity,1, glm::value_ptr(glm::vec3(earthLi, earthLi, earthLi))); 
            
            glUniformMatrix4fv(uMVLocation, // Location
                            1, // Count
                            GL_FALSE, // Transpose
                            glm::value_ptr(modelMat * camera_VM)); // Value   
    }

    void Scene::initAllCubes() {
        for (unsigned int layer = 0; layer < m_width; layer++) {
            for (unsigned int i= 0; i < m_height; i++)
            {
                for(unsigned int j= 0 ; j<m_length ; j++)
                {
                    Cube temp_cube(glm::vec3(i,layer,j));
                    if(layer > 2) {
                        temp_cube.setVisible();
                    }
                    temp_cube.setPositionX((temp_cube.getPosition().x)-1);
                    temp_cube.setPositionY((temp_cube.getPosition().y)-1);
                    m_allCubes.push_back(temp_cube);
                }
            }
        }
    }

    void Scene::drawCubes(FreeFlyCamera &camera) {
        for(unsigned int i = 0 ; i < this->m_width ; i++ ){
            for(unsigned int j = 0 ; j < this->m_length ; j++){
                for(unsigned int k = 0 ; k < this->m_height ; k++){
                    recalculate_matrices(camera,m_allCubes.at(i));
                    if(!this->m_allCubes.at(i).isVisible()) {
                        this->m_allCubes.at(i).draw();
                    }
                }
            }
        }
    }

}