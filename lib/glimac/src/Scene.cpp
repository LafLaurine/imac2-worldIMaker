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
        uMVLocation = glGetUniformLocation(m_programs[type].getGLId(), "uModel");
        std::cout << "value uModelLocation : " << uMVLocation << "id program used uModelLocation : " << m_programs[type].getGLId() << std::endl;
        uMVPLocation = glGetUniformLocation(m_programs[type].getGLId(), "uViewProj");
        uNormalMatLocation = glGetUniformLocation(m_programs[type].getGLId(), "uNormalMat");

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

    void Scene::recalculate_matrices(TrackballCamera &camera,Cube cube) {
            glm::mat4 camera_VM = camera.getViewMatrix();
            glm::mat4 modelMat = glm::translate(glm::mat4(1.0f), cube.getPosition());
            glm::vec4 lightDir4 =  glm::vec4(1.0f, 1.0f, 1.0f, 0.0f);
            lightDir4 = lightDir4 * globalMVMatrix;
            glm::vec3 lightPos = glm::vec3(lightDir4.x, lightDir4.y, lightDir4.z);
            // uLightDir_vs
            glUniform3fv(uLightLocation, 1, glm::value_ptr(lightPos));
            
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
                    if(layer < 3) {
                        temp_cube.setVisible();
                    }
                    m_allCubes.push_back(temp_cube);
                }
            }
        }
    }

    void Scene::drawCubes(TrackballCamera &camera) {
        for(Cube& cube : m_allCubes){
            recalculate_matrices(camera,cube);
            if(cube.isVisible()) {
                cube.draw();
            }
        }
    }

}