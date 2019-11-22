#include <glimac/SDLWindowManager.hpp>
#include <GL/glew.h>
#include <iostream>
#include <cstddef>
#include <math.h>
#include <glimac/Image.hpp>
#include <glimac/Program.hpp> 
#include <glimac/FilePath.hpp> 
#include <glimac/glm.hpp> 
#include <glimac/Sphere.hpp>
#include <glimac/FreeFlyCamera.hpp>

using namespace glimac;

struct EarthProgram {
    Program m_Program;

    GLint uMVPLocation;
    GLint uMVLocation;
    GLint uNormalLocation;
    GLint uTexLocation;
    GLint uCloudTexture;

    EarthProgram(const FilePath& applicationPath):
        m_Program(loadProgram(applicationPath.dirPath() + "shaders/3D.vs.glsl",
                              applicationPath.dirPath() + "shaders/multiTex3D.fs.glsl")) {
        uMVPLocation = glGetUniformLocation(m_Program.getGLId(), "uMVPMatrix");
        uMVLocation = glGetUniformLocation(m_Program.getGLId(), "uMVMatrix");
        uNormalLocation = glGetUniformLocation(m_Program.getGLId(), "uNormalMatrix");
        uTexLocation = glGetUniformLocation(m_Program.getGLId(), "uTexture");
        uCloudTexture = glGetUniformLocation(m_Program.getGLId(), "uCloudTexture");
    }
};

struct MoonProgram {
    Program m_Program;

    GLint uMVPLocation;
    GLint uMVLocation;
    GLint uNormalLocation;
    GLint uTexLocation;

    MoonProgram(const FilePath& applicationPath):
        m_Program(loadProgram(applicationPath.dirPath() + "shaders/3D.vs.glsl",
                              applicationPath.dirPath() + "shaders/tex3D.fs.glsl")) {
        uMVPLocation = glGetUniformLocation(m_Program.getGLId(), "uMVPMatrix");
        uMVLocation = glGetUniformLocation(m_Program.getGLId(), "uMVMatrix");
        uNormalLocation = glGetUniformLocation(m_Program.getGLId(), "uNormalMatrix");
        uTexLocation = glGetUniformLocation(m_Program.getGLId(), "uTexture");
    }
};

int main(int argc, char** argv) {
    const int WINDOW_WIDTH = 800;
    const int WINDOW_HEIGTH = 800;
    // Initialize SDL and open a window
    SDLWindowManager windowManager(WINDOW_WIDTH, WINDOW_HEIGTH, "GLImac");

    // Initialize glew for OpenGL3+ support
    GLenum glewInitError = glewInit();
    if(GLEW_OK != glewInitError) {
        std::cerr << glewGetErrorString(glewInitError) << std::endl;
        return EXIT_FAILURE;
    }

    FilePath applicationPath(argv[0]);
    EarthProgram earthProgram(applicationPath);
    MoonProgram moonProgram(applicationPath);

    std::unique_ptr<Image> textureEarth = loadImage(applicationPath.dirPath() + "../../GLImac-Template/TP3/assets/textures/EarthMap.jpg");
    if (textureEarth == NULL ) std::cout << "Texture couldn't be loaded" << std::endl;

    std::unique_ptr<Image> textureMoon = loadImage(applicationPath.dirPath() + "../../GLImac-Template/TP3/assets/textures/MoonMap.jpg");
    if (textureMoon == NULL ) std::cout << "Texture couldn't be loaded" << std::endl;

    std::unique_ptr<Image> textureCloud = loadImage(applicationPath.dirPath() + "../../GLImac-Template/TP3/assets/textures/CloudMap.jpg");
    if (textureCloud == NULL ) std::cout << "Texture couldn't be loaded" << std::endl;

    std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;

    /*********************************
     * HERE SHOULD COME THE INITIALIZATION CODE
     *********************************/
    /* Creation de la sphere */
    Sphere sphere(1, 32, 32);

    /*Creation VBO et VAO */
    GLuint vbo, vao; 
    const GLuint VERTEX_ATTR_POSITION = 0;
    const GLuint VERTEX_ATTR_NORMAL = 1;
    const GLuint VERTEX_ATTR_TEXT = 2;
    glGenBuffers(1, &vbo);
    glGenVertexArrays(1, &vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    
    glBufferData(GL_ARRAY_BUFFER,
               sphere.getVertexCount() * sizeof(ShapeVertex),
               sphere.getDataPointer(),
               GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(vao);
   
    glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
    glEnableVertexAttribArray(VERTEX_ATTR_NORMAL);
    glEnableVertexAttribArray(VERTEX_ATTR_TEXT);  
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glVertexAttribPointer(
    VERTEX_ATTR_POSITION, // index
    3, // size
    GL_FLOAT, // typetextures
    GL_FALSE, // normalized
    sizeof(ShapeVertex), // stride
    (const GLvoid*) offsetof(ShapeVertex, position) // pointer
    );

    glVertexAttribPointer(
        VERTEX_ATTR_TEXT, // index
        2, // size
        GL_FLOAT, // type
        GL_FALSE, // normalized
        sizeof(ShapeVertex), // stride
        (const GLvoid*) offsetof(ShapeVertex, texCoords) // pointer
    );
  
    glVertexAttribPointer(
        VERTEX_ATTR_NORMAL, // index
        3, // size
        GL_FLOAT, // type
        GL_FALSE, // normalized
        sizeof(ShapeVertex), // stride
        (const GLvoid*) offsetof(ShapeVertex, normal) // pointer
    );        

    //Enable texture earth
    GLuint textures[3];
    glGenTextures(3,textures);
    glBindTexture(GL_TEXTURE_2D, textures[0]);

    glTexImage2D(GL_TEXTURE_2D,
      0,
      GL_RGBA, //internalFormat
      textureEarth->getWidth(), // Width
      textureEarth->getHeight(), // Height
      0, 
      GL_RGBA, // Format
      GL_FLOAT, // Type
      textureEarth->getPixels() // tab pixel
      );
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);

    //Enable texture moon 
    glBindTexture(GL_TEXTURE_2D, textures[1]);
    glTexImage2D(GL_TEXTURE_2D, // Target
        0, // Mipmap level
        GL_RGBA, // Internal Format
        textureMoon->getWidth(), // Width
        textureMoon->getHeight(), // Height
        0, // Border
        GL_RGBA, // Format
        GL_FLOAT, // Type
        textureMoon->getPixels() // Value
    );

        
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);

    //Enable texture cloud 
    glBindTexture(GL_TEXTURE_2D, textures[2]);
    glTexImage2D(GL_TEXTURE_2D, // Target
        0, // Mipmap level
        GL_RGBA, // Internal Format
        textureCloud->getWidth(), // Width
        textureCloud->getHeight(), // Height
        0, // Border
        GL_RGBA, // Format
        GL_FLOAT, // Type
        textureCloud->getPixels() // Value
    );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);

    //Depth activation
    glEnable(GL_DEPTH_TEST);

    glm::mat4 ProjMatrix,MVMatrix, NormalMatrix;
    //Calcul de la matrice de projection
    ProjMatrix = glm::perspective(glm::radians(70.0f),(float) (WINDOW_WIDTH / WINDOW_HEIGTH),0.1f,100.f);

    //Calcul de la matrice MV
    MVMatrix = glm::translate(glm::mat4(), glm::vec3(0, 0, -5));  

    //Calcul de la NormalMatrix 
    NormalMatrix = glm::transpose(glm::inverse(MVMatrix));

    std::vector<glm::vec3> rotationAxes;
    std::vector<glm::vec3> positions;
    for (int i=0; i<32; i++) {
        auto r = glm::sphericalRand(1.f);
        auto p = glm::normalize(glm::cross(r, glm::sphericalRand(1.f))) * 2.5f;
        rotationAxes.push_back(r);
        positions.push_back(p);
    }

    //Create camera
    FreeFlyCamera camera;
    
    // Application loop
    bool done = false;
    while(!done) {
        // Event loop:
        SDL_Event e;
        while(windowManager.pollEvent(e)) {
            if(e.type == SDL_QUIT) {
                done = true; // Leave the loop after this iteration
            }
        }

        switch(e.type) {

          /* Touche clavier */
            case SDL_KEYDOWN: 
            {            
                float zoom = 0.1f;
                if (e.key.keysym.sym == SDLK_z  || e.key.keysym.sym == SDLK_UP) {
                std::cout << "UP pressed" << std::endl;
                camera.moveFront(zoom);
                } 
                else if (e.key.keysym.sym == SDLK_s || e.key.keysym.sym == SDLK_DOWN) {
                std::cout << "DOWN pressed" << std::endl;
                camera.moveFront(-zoom);              
                }

                else if (e.key.keysym.sym == SDLK_q || e.key.keysym.sym == SDLK_LEFT) {
                std::cout << "DOWN pressed" << std::endl;
                camera.moveLeft(zoom);              
                }

                else if (e.key.keysym.sym == SDLK_d || e.key.keysym.sym == SDLK_LEFT) {
                std::cout << "DOWN pressed" << std::endl;
                camera.moveLeft(-zoom);              
                }
            }
            break;
            
            case SDL_MOUSEMOTION: 
            {
                float speed = 0.5f;
                //scroll right
                if (e.motion.xrel != 0 ) {
                camera.rotateUp(float(-e.motion.xrel) * speed);
                }
                else if (e.motion.yrel != 0 ) {
                camera.rotateLeft(float(e.motion.yrel) * speed);
                }
            
            }
            break;

            default:
            break;
        }

        /*********************************
         * HERE SHOULD COME THE RENDERING CODE
         *********************************/
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glBindVertexArray(vao);
        
        //Calcul camera
        glm::mat4 globalMVMatrix =  camera.getViewMatrix();

        /* DESSIN DE LA TERRE */
        earthProgram.m_Program.use();
        glUniform1i(earthProgram.uTexLocation, 0);
        glUniform1i(earthProgram.uCloudTexture, 1);

        glm::mat4 earthMVMatrix = glm::rotate(globalMVMatrix, windowManager.getTime(), glm::vec3(0, 1, 0));
        
        glUniformMatrix4fv(earthProgram.uMVPLocation, // Location
            1, // Count
            GL_FALSE, // Transpose
            glm::value_ptr(ProjMatrix * earthMVMatrix)); // Value
        
        glUniformMatrix4fv(earthProgram.uMVLocation, // Location
            1, // Count
            GL_FALSE, // Transpose
            glm::value_ptr(earthMVMatrix)); // Value

        glUniformMatrix4fv(earthProgram.uNormalLocation, // Location
            1, // Count
            GL_FALSE, // Transpose
            glm::value_ptr(glm::transpose(glm::inverse(earthMVMatrix)))); // Value

        //Draw earth
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textures[0]);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, textures[2]);

        glDrawArrays(GL_TRIANGLES,0,sphere.getVertexCount());

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, 0); // débind sur l'unité GL_TEXTURE0
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, 0); // débind sur l'unité GL_TEXTURE1

        //Moon

        moonProgram.m_Program.use();
        glUniform1i(moonProgram.uTexLocation,0);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textures[1]);

        glm::mat4 moonMVMatrix;

        for(int i = 0; i < 32; i++) {
            moonMVMatrix = glm::rotate(globalMVMatrix, windowManager.getTime(), rotationAxes[i]); // Translation * Rotation     
            moonMVMatrix = glm::translate(moonMVMatrix, positions[i]); // Translation * Rotation * Translation                  MVMatrix = glm::rotate(MVMatrix, windowManager.getTime(), rotationAxes[i]); // Translation * Rotation
            moonMVMatrix = glm::scale(moonMVMatrix, glm::vec3(0.2, 0.2, 0.2)); // Translation * Rotation * Translation * Scale 
            
            //Normale
            glUniformMatrix4fv(
            moonProgram.uNormalLocation, // Location
            1, // Count
            GL_FALSE, // Transpose
            glm::value_ptr(glm::transpose(glm::inverse(moonMVMatrix)))); // Value

            // MVP
            glUniformMatrix4fv(moonProgram.uMVPLocation, // Location
                1, // Count
                GL_FALSE, // Transpose
                glm::value_ptr(ProjMatrix * moonMVMatrix)); // Value
            // MV    
            glUniformMatrix4fv(moonProgram.uMVLocation, // Location
                1, // Count
                GL_FALSE, // Transpose
                glm::value_ptr(moonMVMatrix)); // Value
            //Dessin lune
            glDrawArrays(GL_TRIANGLES,0,sphere.getVertexCount());
        }
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, 0); // débind sur l'unité GL_TEXTURE0
        glBindVertexArray(0);
        // Update the display
        windowManager.swapBuffers();
    }
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
    glDeleteTextures(3, textures);
    return EXIT_SUCCESS;
}
