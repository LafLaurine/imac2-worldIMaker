#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <cstddef>
#include <math.h>
#include <glimac/main.hpp>
#include <glimac/GameController.hpp>
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
#include <imgui/imgui.h>
#include <imgui/imgui_impl_opengl3.h>
#include <imgui/imgui_impl_sdl.h>

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
    //get flatcube program, load it and use it
    ProgramType FlatCube = ProgramType::FlatCube;
    scene.loadProgram(FlatCube,"../shaders/colorCube.vs.glsl","../shaders/colorCube.fs.glsl");
    scene.useProgram(FlatCube);
    //initialize all of the scene cubes
    scene.initAllCubes();
    //initialize imgui
    overlay.initImgui(windowManager.m_window,&windowManager.m_glContext);
    //add light to the scene
    scene.addLight();
    
    SDL_Renderer *renderer = NULL;
	SDL_Texture *img = NULL;
    SDL_Texture *img2 = NULL;

	int w, h; // texture width & height

	renderer = SDL_CreateRenderer(windowManager.m_window, -1, SDL_RENDERER_ACCELERATED);

	img = IMG_LoadTexture(renderer, "./assets/textures/menu.jpg");
	SDL_QueryTexture(img, NULL, NULL, &w, &h); // get the width and height of the texture
	// put the location where we want the texture to be drawn into a rectangle
	// I'm also scaling the texture 2x simply by setting the width and height
	SDL_Rect texr; texr.x = 0; texr.y = 0; texr.w = w; texr.h = h; 


	img2 = IMG_LoadTexture(renderer, "./assets/textures/pause.jpg");
	SDL_QueryTexture(img2, NULL, NULL, &w, &h);

    //set texture
    Texture texture("MoonMap.jpg");
   
    //construct camera
    TrackballCamera camera;
    //construct freefly
    FreeFlyCamera freeCam;
    //set camera position
    camera.setPosMatrix(10,5,5);
    //construct gamecontroller
    GameController gameController;

    //first initialization of uniform matrices
    scene.createUniformMatrices(FlatCube);


    //read control file for tree
    std::vector <ControlPoint> list_ctrlTree;
    readFileControl("controls.txt",list_ctrlTree);
    //read control file for big cube
    std::vector <ControlPoint> list_ctrlCube;
    readFileControl("otherControls.txt",list_ctrlCube);

    //construct cursor
    Cursor cursor;


    // Application loop
    while(windowManager.isRunning()) {
        SDL_Event e;

        while(SDL_PollEvent(&e)) {
            // Send event to ImGui
            ImGui_ImplSDL2_ProcessEvent(&e);

        switch (e.type) {
            
            case SDL_QUIT: windowManager.exit();

            case SDL_MOUSEBUTTONUP:
            if (SDL_BUTTON_LEFT) {
                gameController.inGame();
            }
            break;

            if(gameController.gameOn == true) {
                case SDL_KEYDOWN:
                    gameController.handleScene(e,scene,cursor,overlay,camera);
                    gameController.handleCamera(e,camera);
                    if(e.key.keysym.sym == SDLK_p) {
                        if(!gameController.gamePause) {
                            gameController.pausedGame();
                        }
                        else {
                            gameController.gamePause = false;
                        }
                    }
                default : break;
            }
               
        }
    }

        if(!gameController.gameOn) {
            SDL_RenderClear(renderer);
            // copy the texture to the rendering context
            SDL_RenderCopy(renderer, img, NULL, &texr);
            // flip the backbuffer
            // this means that everything that we prepared behind the screens is actually shown
            SDL_RenderPresent(renderer);
        }

        //Rendering code
        //begin imgui
        if(gameController.gameOn == true) {
            //set background color
            glClearColor(0.4, 0.6, 0.2, 1);
            overlay.beginFrame(windowManager.m_window);
           
           
            if(!gameController.gamePause) {
            //draw tools
            overlay.drawOverlay(scene);
            //draw cubes
            scene.drawCubes(camera, texture.m_textureId);
            //add lights
            scene.addLight();
            scene.recalculateMatrices(camera,cursor);
            //draw cursor
            cursor.draw();

            //handle click on the overlay
            if(overlay.getClickedTree() &1) {
                applyRbf(scene.getAllCubes(), list_ctrlTree, FunctionType::InverseQuadratic);
            }
            if(overlay.getClickedCube() &1) {
                applyRbf(scene.getAllCubes(), list_ctrlCube, FunctionType::Gaussian);
            }
            if(overlay.getClickedReset() &1) {
                gameController.cleanScene(scene.getAllCubes());
            }
            if(overlay.getClickedAddCube() &1) {
                gameController.addCube(scene,cursor);
            }
            if(overlay.getClickedDeleteCube() &1) {
                gameController.deleteCube(scene,cursor);
            }
            if(overlay.getClickedAddTexture() &1) {
                gameController.setTextureCube(scene,cursor, texture);
            }
            if(overlay.getClickedRemoveTexture() &1) {
               // gameController.removeTextureCube(scene,cursor, texture);
            }

            }
            //end imgui
            overlay.endFrame(windowManager.m_window);
        }

    }
    SDL_DestroyRenderer(renderer); 
    return EXIT_SUCCESS;
}