#include <glimac/Scene.hpp>
#include <iostream>
#include <glm/gtc/type_ptr.hpp>
#include <glimac/gl-exception.hpp>


namespace glimac {
    void Scene::loadProgram(ProgramType type, std::string vertexShader, std::string fragmentShader) {
        m_programs.emplace(type, glimac::loadProgram(vertexShader,fragmentShader));
    }

    void Scene::useProgram(ProgramType type) {
        m_programs[type].use();
    }

    void Scene::createUniformMatrices(ProgramType type)
    {
        //set all of the uniform matrices
        uColorLocation = glGetUniformLocation(m_programs[type].getGLId(), "uColor");
        uMVLocation = glGetUniformLocation(m_programs[type].getGLId(), "uModelView");
        uMVPLocation = glGetUniformLocation(m_programs[type].getGLId(), "uViewProj");
        uNormalMatLocation = glGetUniformLocation(m_programs[type].getGLId(), "uNormalMat");
        uLightPosLocation = glGetUniformLocation(m_programs[type].getGLId(), "uLightPos_vs");
        uKs = glGetUniformLocation(m_programs[type].getGLId(), "uKs");
        uShininess = glGetUniformLocation(m_programs[type].getGLId(), "uShininess");
        uLightDir_vs = glGetUniformLocation(m_programs[type].getGLId(), "uLightDir_vs");
        uLightIntensityP = glGetUniformLocation(m_programs[type].getGLId(), "uLightIntensityP");
        uLightIntensityD = glGetUniformLocation(m_programs[type].getGLId(), "uLightIntensityD");
        uAmbiantLight = glGetUniformLocation(m_programs[type].getGLId(), "ambiantLightIntensity");
        uTextureLocation = glGetUniformLocation(m_programs[type].getGLId(), "uTexture");
        uIsThereTexture = glGetUniformLocation(m_programs[type].getGLId(), "setTexture");
        uCubeTypeLocation = glGetUniformLocation(m_programs[type].getGLId(), "uCubeType");

        //compute the model matrix
        glm::mat4 modelMat = glm::mat4(1.0f);

        glUniformMatrix4fv(uMVLocation, // Location
                            1, // Count
                            GL_FALSE, // Transpose
                            glm::value_ptr(modelMat)); // Value

        //compute the model view and projection matrices
        MVMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -10.0f));
        ProjMatrix = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 100.0f);
        glm::mat4 viewProjMat = ProjMatrix * MVMatrix;
        glm::mat4 normalMat = glm::transpose(glm::inverse(MVMatrix));
        glUniform1i(uIsThereTexture,0);
        glUniform1i(uCubeTypeLocation,0);

        glUniformMatrix4fv(uMVPLocation, // Location
                                1, // Count
                                GL_FALSE, // Transpose
                                glm::value_ptr(viewProjMat)); // Value

        glUniformMatrix4fv(uNormalMatLocation, // Location
                        1, // Count
                        GL_FALSE, // Transpose
                        glm::value_ptr(normalMat)); // Value
        
    }

    void Scene::recalculateMatrices(FreeFlyCamera &camera,Cube cube) {
        //compute the model view matrix with the camera
        float xCube = cube.getPosition().x;
        float yCube = cube.getPosition().y;
        float zCube = cube.getPosition().z;
        glm::vec3 cubePos = {xCube, yCube, zCube};
        glm::mat4 camera_VM = camera.getViewMatrix();
        glm::mat4 modelMat = glm::translate(glm::mat4(1.0f), cubePos);
        glUniform3fv(uColorLocation, 1, glm::value_ptr(cube.getColor()));
        glUniformMatrix4fv(uMVLocation, // Location
                            1, // Count
                            GL_FALSE, // Transpose
                            glm::value_ptr(modelMat * camera_VM)); // Value   
            
    }

    void Scene::addLight() {
        //point light on/off
        pointLight = 0; 
        //directive light on/off
        directiveLight = 0;

        //directive light position
        xLightD = -1.0f;
        yLightD = -1.0f;
        zLightD = -1.0f;

        //point light position
        xLightP = 1.0f;
        yLightP = 1.0f;
        zLightP = 1.0f;

        //compute Kd,Ks and shininess of the light
        glUniform3f(uKs, 0, 0.0, 0.0);
        glUniform1f(uShininess, 25.0);
        glUniform3f(uAmbiantLight,0.2,0.2,0.2);
        //compute light of the point light
        glm::vec4 LightPos = MVMatrix * glm::vec4(xLightP, yLightP, zLightP, 1);
        glUniform3f(uLightPosLocation, LightPos.x, LightPos.y, LightPos.z);
        //compute light of the directionnal light
        glm::vec4 LightDir = MVMatrix * glm::vec4(xLightD, yLightD, zLightD, 1);
        glUniform3f(uLightDir_vs, LightDir.x, LightDir.y, LightDir.z);
    }

    void Scene::changeLuminosity(int dirLight, int pointLight) {
        //Day/night for directionnal lights
        if (dirLight == 0){
            glUniform3f(uLightIntensityD, 2.0, 2.0, 2.0);   
        }
        else {
            glUniform3f(uLightIntensityD, 0.0, 0.0, 0.0);
        }
        //Day/night for point light
        if (pointLight == 0){
            glUniform3f(uLightIntensityP, 2.0, 2.0, 2.0);   
        }
        else {
            glUniform3f(uLightIntensityP, 0.0, 0.0, 0.0);
        }
    }

    void Scene::changeIntensityAmbiant(float &x, float &y, float &z) {
        glUniform3f(uAmbiantLight,x,y,z);
    }

    void Scene::changeIntensityDirectional(float &x, float &y, float &z) {
        glUniform3f(uLightIntensityD, x, y, z);
    }

    void Scene::changeIntensityPoint(float &x, float &y, float &z) {
        glUniform3f(uLightIntensityP, x, y, z);
    }

    void Scene::changePointLightPosition(float pointLightX, float pointLightY, float pointLightZ) {
        //recalculate point light position if moved
        glUniform3f(uLightPosLocation, pointLightX, pointLightY, pointLightZ);
    }

    void Scene::changeDirectiveLightPosition(float directiveLightX, float directiveLightY, float directiveLightZ) {        
        //recalculate directionnal light position if moved
        glUniform3f(uLightDir_vs, directiveLightX, directiveLightY, directiveLightZ);
    }

    void Scene::setGround() {
        for (unsigned int z = 0; z < m_length ; z++) {
                for(unsigned int x= 0 ; x<m_width ; x++)
                {
                    Cube cube(glm::ivec3(x,0,z));
                    m_allCubes.push_back(cube);
                    tabCubes[x][0][z] = &m_allCubes.back();
                }
        }
    }
}
