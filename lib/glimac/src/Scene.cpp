#include <glimac/Scene.hpp>
#include <iostream>
#include <glm/gtc/type_ptr.hpp>

namespace glimac {
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
        uColorLocation = glGetUniformLocation(m_programs[type].getGLId(), "uColor");
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
            glUniform3fv(uColorLocation, 1, glm::value_ptr(cube.getColor()));
            
            glUniformMatrix4fv(uMVLocation, // Location
                            1, // Count
                            GL_FALSE, // Transpose
                            glm::value_ptr(modelMat * camera_VM)); // Value   
    }

    void Scene::addLight() {
        glm::vec4 lightDir4 =  glm::vec4(1.0f, 1.0f, 1.0f, 0.0f);
        lightDir4 = lightDir4 * globalMVMatrix;
        glm::vec3 lightPos = glm::vec3(lightDir4.x, lightDir4.y, lightDir4.z);
        // uLightDir_vs
        glUniform3fv(uLightLocation, 1, glm::value_ptr(lightPos));
    }

    void Scene::removeLight() {
        glm::vec3 lightPos = glm::vec3(0.0f, 0.0f, 0.0f);
        glUniform3fv(uLightLocation, 1, glm::value_ptr(lightPos));   
    }

    void Scene::setGround() {
        for(unsigned int x = 0; x < m_width; x++) {
            for(unsigned int z = 0; z < m_length; z++) {
                m_allCubes.at(from1Dto3D(glm::ivec3(x,0,z))).setVisible();
            }
        }
    }

    void Scene::initAllCubes() {
        for (unsigned int z = 0; z < m_length; z++) {
            for (unsigned int y= 0; y < m_height; y++)
            {
                for(unsigned int x= 0 ; x<m_width ; x++)
                {
                    Cube temp_cube(glm::vec3(x,y,z));
                    m_allCubes.push_back(temp_cube);
                }
            }
        }
        //set ground
        setGround();
    }

    void Scene::drawCubes(TrackballCamera &camera) {
        for(Cube& cube : m_allCubes){
            addLight();
            recalculate_matrices(camera,cube);
            if(cube.isVisible()) {
                cube.draw();
            }
        }
    }

    void Scene::drawCursor(Cursor& cursor){
        cursor.draw();
    }

    unsigned int Scene::from1Dto3D(glm::ivec3 pos) {
        return (pos.y * m_width + pos.x + pos.z * m_width * m_length);
    }
}
