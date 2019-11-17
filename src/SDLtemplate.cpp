#include <glimac/SDLWindowManager.hpp>
#include <GL/glew.h>
#include <iostream>
#include <cstddef>
#include <math.h>
#include <glimac/Program.hpp> 
#include <glimac/FilePath.hpp> 
#include <glimac/glm.hpp> 
#include <glimac/Sphere.hpp>

using namespace glimac;

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
    Program program = loadProgram(applicationPath.dirPath() + "shaders/3D.vs.glsl",
                                  applicationPath.dirPath() + "shaders/normal.fs.glsl");
    program.use();

    //Recupère variables uniformes
    GLint uMVPLocation = glGetUniformLocation(program.getGLId(), "uMVPMatrix");
    GLint uMVLocation = glGetUniformLocation(program.getGLId(), "uMVMatrix");
    GLint uNormalLocation = glGetUniformLocation(program.getGLId(), "uNormalMatrix");

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
    const GLuint VERTEX_ATTR_COORDS = 2;
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
    glEnableVertexAttribArray(VERTEX_ATTR_COORDS);  
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glVertexAttribPointer(
    VERTEX_ATTR_POSITION, // index
    3, // size
    GL_FLOAT, // type
    GL_FALSE, // normalized
    sizeof(ShapeVertex), // stride
    (const GLvoid*) offsetof(ShapeVertex, position) // pointer
    );

    glVertexAttribPointer(
        VERTEX_ATTR_COORDS, // index
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

    glEnable(GL_DEPTH_TEST);

    glm::mat4 ProjMatrix,MVMatrix, NormalMatrix;
    //Calcul de la matrice de projection
    ProjMatrix = glm::perspective(glm::radians(70.f),(float) (WINDOW_WIDTH / WINDOW_HEIGTH),0.1f,100.f);

    //Calcul de la matrice MV
    MVMatrix = glm::translate(glm::mat4(), glm::vec3(0, 0, -5));  

    //Calcul de la NormalMatrix 
    NormalMatrix = glm::transpose(glm::inverse(MVMatrix));

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

        /*********************************
         * HERE SHOULD COME THE RENDERING CODE
         *********************************/
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glm::mat4 modelMatrix;
        glUniformMatrix4fv(uMVPLocation, // Location
                    1, // Count
                    GL_FALSE, // Transpose
                    glm::value_ptr(ProjMatrix * MVMatrix)); // Value
        
        glUniformMatrix4fv(uMVLocation, // Location
                    1, // Count
                    GL_FALSE, // Transpose
                    glm::value_ptr(MVMatrix)); // Value

        glUniformMatrix4fv(uNormalLocation, // Location
                    1, // Count
                    GL_FALSE, // Transpose
                    glm::value_ptr(NormalMatrix)); // Value

        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES,0,sphere.getVertexCount());

        glBindVertexArray(0);
        // Update the display
        windowManager.swapBuffers();
    }

    return EXIT_SUCCESS;
}
