#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <iostream>
#include <cstddef>
#include <math.h>
#include "./Sound.hpp"
#include <glimac/main.hpp>
#include <glimac/GameController.hpp>
#include <glimac/PlayerController.hpp>
#include <glimac/TrackballCamera.hpp>
#include <glimac/FreeFlyCamera.hpp>
#include <glimac/SDLWindowManager.hpp> 
#include <glimac/FilePath.hpp> 
#include <glimac/Overlay.hpp>
#include <glimac/File.hpp>
#include <glimac/Cube.hpp>
#include <glimac/Scene.hpp>
#include <glimac/Cursor.hpp>
#include <glimac/Texture.hpp>
#include <glimac/Menu.hpp>

using namespace glimac;

int main(int argc, char** argv) {    
    constexpr int WINDOW_WIDTH = 1200;
    constexpr int WINDOW_HEIGHT = 1200;

    // Initialize SDL and open a window
    SDLWindowManager windowManager(WINDOW_WIDTH, WINDOW_HEIGHT, "worldIMaker");
    SDL_WarpMouseInWindow(windowManager.m_window, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2); // set users mouse position to the center  

    //construct overlay
    Overlay overlay;
    //construct scene
    Scene scene;

    ProgramType typeMenu = ProgramType::Menu;
    Sound soundPlayer;
    soundPlayer.play(BACKGROUND);

    Menu menu(scene,typeMenu,"menu.jpg");
    Menu pause(scene,typeMenu,"pause.jpg");

    //get flatcube program, load it and use it
    ProgramType FlatCube = ProgramType::FlatCube;
    scene.loadProgram(FlatCube,"../shaders/colorCube.vs.glsl","../shaders/colorCube.fs.glsl");
    scene.useProgram(FlatCube);
    //initialize all of the scene cubes
    //gameController.initAllCubes();
    //initialize imgui
    overlay.initImgui(windowManager.m_window,&windowManager.m_glContext);
    //add light to the scene
    scene.addLight();
    //set texture
    Texture groundTree("groundTree.jpg");
    //texture tree
    Texture tree("tree.jpg");
    //construct camera
    TrackballCamera camera;
    //construct freefly
    FreeFlyCamera freeCam;
    //set camera position
    camera.setPosMatrix(10,5,5);
    //construct cursor
    Cursor cursor;
    //construct gamecontroller
    GameController gameController(&scene, &cursor);
    PlayerController playerController;
    //first initialization of uniform matrices
    scene.createUniformMatrices(FlatCube);

    //read control file for tree
    std::vector <ControlPoint> list_ctrlTree;
    readFileControl("controls.txt",list_ctrlTree);
    //read control file for big cube
    std::vector <ControlPoint> list_ctrlCube;
    readFileControl("test1.txt",list_ctrlCube);
    gameController.initAllCubes();

    // Application loop
    while(windowManager.isRunning()) {
        SDL_Event e;

        while(SDL_PollEvent(&e)) {
            // Send event to ImGui
            ImGui_ImplSDL2_ProcessEvent(&e);

            switch (e.type) {
                
                case SDL_QUIT: windowManager.exit();

                case SDL_MOUSEBUTTONUP:
                    int x, y;
                    SDL_GetMouseState(&x, &y);
                    if (SDL_BUTTON_LEFT) {
                        if(floatIsBetween(x, 301, 900) && floatIsBetween(y, 400, 500)){
                            playerController.inGame();
                        }
                        if(floatIsBetween(x, 331, 658) && floatIsBetween(y, 600, 700)){
                            playerController.loadGame();
                        }
                    }
                break;

                if(playerController.gameOn == true) {
                    case SDL_KEYDOWN:
                    if(!ImGui::GetIO().WantCaptureKeyboard) {
                        gameController.handleScene(e,overlay,camera);
                        playerController.handleCamera(e,camera);
                        if(e.key.keysym.sym == SDLK_ESCAPE) {
                            windowManager.exit();
                        }
                        if(e.key.keysym.sym == SDLK_p) {
                            if(!playerController.gamePause) {
                                playerController.pausedGame();
                            }
                            else {
                                playerController.gamePause = false;
                            }
                        }
                    }
                        
                    default : break;
                }  
            }
        }

        overlay.beginFrame(windowManager.m_window);

        //Rendering code
        if(!playerController.gameOn) {
            menu.draw(scene,typeMenu);
        }

        if(playerController.gameOn == true) {
            scene.useProgram(FlatCube);
            //set background color
            glClearColor(0.17, 0.19, 0.17, 1);
            
            if(playerController.gamePause) {
                pause.draw(scene,typeMenu); 
            }

            if(!playerController.gamePause) {
                //draw tools
                overlay.drawOverlay(scene);
                //draw cubes
                if(playerController.gameLoad == true) {
                    loadFile("./assets/doc/", "world.txt", scene.getAllCubes(),scene);
                }
                gameController.drawCubes(camera, groundTree);
                //add lights
                scene.addLight();
                scene.recalculateMatrices(camera,cursor);
                //draw cursor
                cursor.draw();

                //handle click on the overlay
                if(overlay.getClickedTree() &1) {
                    applyRbf(scene.getAllCubes(), list_ctrlTree, FunctionType::InverseQuadratic, gameController);
                }
                if(overlay.getClickedCube() &1) {
                    applyRbf(scene.getAllCubes(), list_ctrlCube, FunctionType::ThinPlateSpline, gameController);
                }
                if(overlay.getClickedReset() &1) {
                    gameController.cleanScene(scene.getAllCubes());
                }
                if(overlay.getClickedAddCube() &1) {
                    if(gameController.addToCursor())
                        soundPlayer.play(BUILD);
                }
                if(overlay.getClickedDeleteCube() &1) {
                    if(gameController.deleteToCursor())
                        soundPlayer.play(DESTROY);
                }
                if(overlay.getClickedAddTexture() &1) {
                    gameController.setTextureCube(groundTree);
                }
                if(overlay.getClickedRemoveTexture() &1) {
                    gameController.removeTextureCube(groundTree);
                }

            }
        }
        //end imgui        
        overlay.endFrame(windowManager.m_window);

    }
    return EXIT_SUCCESS;
}