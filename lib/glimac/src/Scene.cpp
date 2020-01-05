#include <glimac/Scene.hpp>
#include <iostream>
#include <glm/gtc/type_ptr.hpp>

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
        uMVLocation = glGetUniformLocation(m_programs[type].getGLId(), "uModel");
        uMVPLocation = glGetUniformLocation(m_programs[type].getGLId(), "uViewProj");
        uNormalMatLocation = glGetUniformLocation(m_programs[type].getGLId(), "uNormalMat");
        uLightPosLocation = glGetUniformLocation(m_programs[type].getGLId(), "uLightPos_vs");
        uKd = glGetUniformLocation(m_programs[type].getGLId(), "uKd");
        uKs = glGetUniformLocation(m_programs[type].getGLId(), "uKs");
        uShininess = glGetUniformLocation(m_programs[type].getGLId(), "uShininess");
        uLightDir_vs = glGetUniformLocation(m_programs[type].getGLId(), "uLightDir_vs");
        uLightIntensityP = glGetUniformLocation(m_programs[type].getGLId(), "uLightIntensityP");
        uLightIntensityD = glGetUniformLocation(m_programs[type].getGLId(), "uLightIntensityD");
        uTextureLocation = glGetUniformLocation(m_programs[type].getGLId(), "uTexture");
        uIsThereTexture = glGetUniformLocation(m_programs[type].getGLId(), "setTexture");

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

        glUniformMatrix4fv(uMVPLocation, // Location
                                1, // Count
                                GL_FALSE, // Transpose
                                glm::value_ptr(viewProjMat)); // Value

        glUniformMatrix4fv(uNormalMatLocation, // Location
                        1, // Count
                        GL_FALSE, // Transpose
                        glm::value_ptr(normalMat)); // Value
        
    }

    void Scene::recalculateMatrices(TrackballCamera &camera,Cube cube) {
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
        glUniform3f(uKd, 0.6, 0.6, 0.6);
        glUniform3f(uKs, 0, 0.0, 0.0);
        glUniform1f(uShininess, 30.0);
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
            glUniform3f(uLightIntensityD, 3.0, 3.0, 3.0);   
        }
        else {
            glUniform3f(uLightIntensityD, 0.0, 0.0, 0.0);
        }
        //Day/night for point light
        if (pointLight == 0){
            glUniform3f(uLightIntensityP, 4.0, 4.0, 4.0);   
        }
        else {
            glUniform3f(uLightIntensityP, 0.0, 0.0, 0.0);
        }
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

    /*void Scene::setGround() {
        //set plain ground
        for(unsigned int x = 0; x < m_width; x++) {
            for(unsigned int z = 0; z < m_length; z++) {
                //m_allCubes.at(from3Dto1D(glm::ivec3(x,0,z))).setVisible();
                std::cout << tabCubes[x][0][z] << std::endl;
                (tabCubes[x][0][z])->setVisible();
            }
        }
    }*/

    /*void Scene::initAllCubes() {
        //initialize all the cube of the scene
        for (unsigned int z = 0; z < m_length ; z++) {
            for(unsigned int x= 0 ; x < m_width ; x++) {
                //this->m_cubeConstruct.setPosition(glm::ivec3(x,y,z));
                Cube cube(glm::ivec3(x,y,z));
                m_allCubes.push_back(cube);
                tabCubes[x][0][z] = &m_allCubes.back();

            }
        }
        setGround();
    }*/

    /* enlever logique visible invisible : 
    - aller a l'endroit ou cube sont rendus et enlever condition qui voit si cube visible ou pas et on les rend tous
    - passer le vecteur en liste #include <list
    - foreach, iterateur fonction lambda   std::iterator vector.for_each(vector.begin(), vector.end(),  fonction lambda)
    fonction lambda[] dans corchets, tous les trucs  qu'on recupere de l'exterieur, dans () stocke le cube actuel pour chaque iteration (on donne type et nom), dans {} tout ce qu'on veut faire pour chaque cube
    - on veut enlever initAllcubes, juste le sol et on appelera addcube.
    déplacer fonction qui permet d'initiliser le sol dans gamecontroller
    - changer add cube et tout en enlenvant setVisible et en le mettant direct dans le vect avec un pushBack()
    */
    
    //convert a 3D vector to a 1D one
    unsigned int Scene::from3Dto1D(glm::ivec3 pos) {
        return (pos.y * m_width + pos.x + pos.z * m_width * m_length);
    }
}
