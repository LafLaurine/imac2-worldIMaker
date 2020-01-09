#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <iostream>
#include <cstddef>
#include <math.h>
#include "./Sound.hpp"
#include <glimac/main.hpp>
#include <glimac/GameController.hpp>
#include <glimac/PlayerController.hpp>
#include <glimac/SDLWindowManager.hpp> 
#include <glimac/FilePath.hpp> 
#include <glimac/File.hpp>
#include <glimac/Scene.hpp>
#include <glimac/Cursor.hpp>
#include <glimac/Texture.hpp>
#include <glimac/Menu.hpp>
#include <list>
#include <algorithm>

using namespace glimac;

int main(int argc, char** argv) {    
    // Initialize SDL and open a window
    SDLWindowManager windowManager(WINDOW_WIDTH, WINDOW_HEIGHT, "worldIMaker");
    SDL_WarpMouseInWindow(windowManager.m_window, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2); // set users mouse position to the center  

    //construct overlay
    Overlay overlay;
    //construct scene
    Scene scene;
    //construct type program for menu
    ProgramType typeMenu = ProgramType::Menu;
    //set background music
    Sound soundPlayer;
    soundPlayer.play(BACKGROUND);
    //load menu for principal menu and pause
    Menu menu(scene,typeMenu,"menu.jpg");
    Menu pause(scene,typeMenu,"pause.jpg");

    //get colorcube program, load it and use it
    ProgramType Cube = ProgramType::Cube;
    scene.loadProgram(Cube,"../shaders/colorCube.vs.glsl","../shaders/colorCube.fs.glsl");
    scene.useProgram(Cube);
    //initialize imgui
    overlay.initImgui(windowManager.m_window,&windowManager.m_glContext);
    //add light to the scene
    scene.addLight();
    //load texture
    Texture ground("groundTree.jpg");
    Texture wood("wood.png");
    Texture gold("gold.jpeg");
    Texture grass("grass.jpeg");
    Texture iron("iron.jpeg");
    Texture pig("pig.jpeg");
    //construct camera
    FreeFlyCamera camera;
    //construct cursor
    Cursor cursor;
    //construct gamecontroller
    GameController gameController(&scene, &cursor);
    //construct playercontroller
    PlayerController playerController;
    //first initialization of uniform matrices
    scene.createUniformMatrices(Cube);
    scene.calculateMatrices();
    //read control file for tree
    std::vector <ControlPoint> list_ctrlRBF;
    readFileControl("controls.txt",list_ctrlRBF);
    //read control file for big cube
    std::vector <ControlPoint> list_ctrlCube;
    readFileControl("multiquadratic.txt",list_ctrlCube);

    //init all cube of the scene
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
                            loadFile("./assets/doc/", "world.txt", scene.getAllCubes(),scene);
                        }
                    }
                break;

                if(playerController.getGameOn() == true) {
                    case SDL_KEYDOWN:
                    if(!ImGui::GetIO().WantCaptureKeyboard) {
                        gameController.handleScene(e,overlay,camera);
                        playerController.handleCamera(e,camera);
                        if(e.key.keysym.sym == SDLK_ESCAPE) {
                            windowManager.exit();
                        }
                        if(e.key.keysym.sym == SDLK_p) {
                            if(!playerController.getGamePause()) {
                                playerController.pausedGame();
                            }
                            else {
                                playerController.setGamePauseF();
                            }
                        }
                    }
                        
                    default : break;
                }  
            }
        }

        overlay.beginFrame(windowManager.m_window);

        //Rendering code
        if(!playerController.getGameOn()) {
            menu.draw(scene,typeMenu);
        }

        if(playerController.getGameOn() == true) {
            scene.useProgram(Cube);
            //set background color
            glClearColor(0.17, 0.19, 0.17, 1);
            
            if(playerController.getGamePause()) {
                pause.draw(scene,typeMenu); 
            }

            if(!playerController.getGamePause() || playerController.getGameLoad() == true) {
                //draw tools
                overlay.drawOverlay(scene);
                //draw cubes
                gameController.drawCubes(camera, ground);
                //add lights
                scene.addLight();
                scene.recalculateMatrices(camera,cursor);
                //draw cursor
                cursor.draw();
                //handle click on the overlay
                if(overlay.getClickedRBF() &1) {
                    applyRbf(scene.getAllCubes(), list_ctrlRBF, FunctionType::InverseQuadratic, gameController,scene);
                }
                if(overlay.getClickedCube() &1) {
                    applyRbf(scene.getAllCubes(), list_ctrlCube, FunctionType::Multiquadric, gameController,scene);
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
                if(overlay.getClickedAddTextureGround() &1) {
                    gameController.setTextureCube(ground);
                }
                if(overlay.getClickedAddTextureGold() &1) {
                    gameController.setTextureCube(gold);
                }
                if(overlay.getClickedAddTextureWood() &1) {
                    gameController.setTextureCube(wood);
                }
                if(overlay.getClickedAddTextureGrass() &1) {
                    gameController.setTextureCube(grass);
                }
                if(overlay.getClickedAddTextureIron() &1) {
                    gameController.setTextureCube(iron);
                }
                if(overlay.getClickedAddTexturePig() &1) {
                    gameController.setTextureCube(pig);
                }
                if(overlay.getClickedRemoveTexture() &1) {
                    gameController.removeTextureCube();
                }

            }
        }
        //end imgui        
        overlay.endFrame(windowManager.m_window);

    }
    return EXIT_SUCCESS;
}