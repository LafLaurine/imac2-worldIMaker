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
        uMVPLocation = glGetUniformLocation(m_programs[type].getGLId(), "uViewProj");
        uNormalMatLocation = glGetUniformLocation(m_programs[type].getGLId(), "uNormalMat");
        uColorLocation = glGetUniformLocation(m_programs[type].getGLId(), "uColor");
        uLightPosLocation = glGetUniformLocation(m_programs[type].getGLId(), "uLightPos_vs");
        uKd = glGetUniformLocation(m_programs[type].getGLId(), "uKd");
        uKs = glGetUniformLocation(m_programs[type].getGLId(), "uKs");
        uShininess = glGetUniformLocation(m_programs[type].getGLId(), "uShininess");
        uLightDir_vs = glGetUniformLocation(m_programs[type].getGLId(), "uLightDir_vs");
        uLightIntensityP = glGetUniformLocation(m_programs[type].getGLId(), "uLightIntensityP");
        uLightIntensityD = glGetUniformLocation(m_programs[type].getGLId(), "uLightIntensityD");
    
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
        pointLight = 0; // Spotlight on/off
        directiveLight = 0; // Directive light on/off

        // Directive light position
        xLightD = -1.0f;
        yLightD = -1.0f;
        zLightD = -1.0f;

        // Spotlight position
        xLightP = 1.0f;
        yLightP = 1.0f;
        zLightP = 1.0f;

        glUniform3f(uKd, 0.6, 0.6, 0.6);
        glUniform3f(uKs, 0, 0.0, 0.0);
        glUniform1f(uShininess, 30.0);
        glm::vec4 LightPos = MVMatrix * glm::vec4(xLightP, yLightP, zLightP, 1);
        glUniform3f(uLightPosLocation, LightPos.x, LightPos.y, LightPos.z);
        glm::vec4 LightDir = MVMatrix * glm::vec4(xLightD, yLightD, zLightD, 1);
        glUniform3f(uLightDir_vs, LightDir.x, LightDir.y, LightDir.z);
    }

    void Scene::changeLuminosity(int dirLight, int pointLight) {
        // Day / night
        if (dirLight == 0){
            glUniform3f(uLightIntensityD, 2.0, 2.0, 2.0);   
        }
        else {
            glUniform3f(uLightIntensityD, 0.0, 0.0, 0.0);
        }
        if (pointLight == 0){
            glUniform3f(uLightIntensityP, 2.0, 2.0, 2.0);   
        }
        else {
            glUniform3f(uLightIntensityP, 0.0, 0.0, 0.0);
        }
    }

    void Scene::changePointLightPosition(float pointLightX, float pointLightY, float pointLightZ) {
        glUniform3f(uLightPosLocation, pointLightX, pointLightY, pointLightZ);
    }

    void Scene::changeDirectiveLightPosition(float directiveLightX, float directiveLightY, float directiveLightZ) {
        glUniform3f(uLightDir_vs, directiveLightX, directiveLightY, directiveLightZ);
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
            recalculate_matrices(camera,cube);
            if(cube.isVisible()) {
                cube.draw();
            }
        }
    }
    
    unsigned int Scene::from1Dto3D(glm::ivec3 pos) {
        return (pos.y * m_width + pos.x + pos.z * m_width * m_length);
    }
}
