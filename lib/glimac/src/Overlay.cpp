#include "glimac/Overlay.hpp"
#include <iostream>
#include <imgui/imgui_stdlib.h>
#include <glimac/File.hpp>

namespace glimac {

    Overlay::~Overlay() {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplSDL2_Shutdown();
        ImGui::DestroyContext();
    }
    void Overlay::initImgui(SDL_Window* window,SDL_GLContext* glContext) const {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGui::StyleColorsDark();
        ImGui_ImplSDL2_InitForOpenGL(window,&glContext);
        ImGui_ImplOpenGL3_Init("#version 330 core");
    }

    void Overlay::beginFrame(SDL_Window* window) const {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame(window);
        ImGui::NewFrame();
    }

    void Overlay::drawOverlay(Scene &scene) {
        ImGui::Begin("Tools",&p_open,ImGuiWindowFlags_NoMove | ImGuiWindowFlags_MenuBar  |ImGuiWindowFlags_NoCollapse);
        {
            //set color picker
            ImGui::ColorEdit4("Color", this->getColor());
            //set clicked variables to communicate with the main
            clickedAddCube = 0;
            clickedDeleteCube = 0;
            clickedTree = 0;
            clickedCube = 0;
            clickedReset = 0;
            clickedAddTexture = 0;
            clickedChangeCamera = 0;

            //set buttons
            if (ImGui::Button("Reset")) 
            {
                clickedReset++;
            }

            if (ImGui::Button("Add cube")) {
                clickedAddCube++;
            }
            
            if (ImGui::Button("Add texture")) 
            {
                clickedAddTexture++;
            }
            if (ImGui::Button("Destroy cube")) 
            { 
                clickedDeleteCube++;
            }
            
            if (ImGui::Button("Set ground")) 
            {
                scene.setGround();
            }

            if (ImGui::Button("Generate tree")) 
            {
                clickedTree++;
            }

            if (ImGui::Button("Generate big cube")) 
            {
               clickedCube++;
            }

            //change camera
            if (ImGui::Button("Change camera")) 
            {
                clickedChangeCamera++;
            }
        }
        ImGui::End();

        //set the save and load window
        ImGui::Begin("Save and load",&p_open);
        {
            //set strings for save and load filepath and filename
            static std::string filePath = "./assets/doc/";
            static std::string filename = "world.txt";

            static std::string loadFilePath = "./assets/doc/";
            static std::string loadFilename = "world.txt";
            ImGui::Text("Save file :");
            ImGui::InputText("Path", &filePath);
            ImGui::InputText("Filename", &filename);
            if (ImGui::Button("Save"))
            {
                //save file with filepath and filename of the user choice
                saveFile(filePath,filename,scene.getAllCubes());
            }

            ImGui::Text("Load file :");
            ImGui::InputText("Path", &loadFilePath);
            ImGui::InputText("Filename", &loadFilename);

            if (ImGui::Button("Load"))
            {
                //load file with filepath and filename of the user choice
                loadFile(loadFilePath, loadFilename, scene.getAllCubes());
            }
        }
        ImGui::End();

        //light settings windows
        ImGui::Begin("Light",&p_open); {

            //set few variables that came from the scene in order to start with the right settings of the two lights
            static int dirLight = scene.getDirectiveLight();
            static float dirLightX = scene.getLightXD();
            static float dirLightY = scene.getLightYD();
            static float dirLightZ = scene.getLightZD();

            static int pointLight = scene.getPointLight();
            static float pointLightX = scene.getLightXP();
            static float pointLightY = scene.getLightYP();
            static float pointLightZ = scene.getLightZP();

            const char* itemsLight[] = { "On", "Off"};

            //Directionnal light
            ImGui::Text("Directionnal light :");
            ImGui::Combo("D", &dirLight, itemsLight, IM_ARRAYSIZE(itemsLight));
            ImGui::Text("Coordinates D");
            ImGui::InputFloat("xD",&dirLightX);
            ImGui::Text("Y :");
            ImGui::InputFloat("yD", &dirLightY);
            ImGui::Text("Z :");
            ImGui::InputFloat("zD", &dirLightZ);

            // Point light
            ImGui::Text("Point light :");
            ImGui::Combo("P", &pointLight, itemsLight, IM_ARRAYSIZE(itemsLight));
            ImGui::Text("Coordinates P");
            ImGui::InputFloat("xP", &pointLightX);
            ImGui::Text("Y :");
            ImGui::InputFloat("yP", &pointLightY);
            ImGui::Text("Z :");
            ImGui::InputFloat("zP", &pointLightZ);
            scene.changeLuminosity(dirLight, pointLight);
            scene.changeDirectiveLightPosition(dirLightX,dirLightY,dirLightZ);
        }
        ImGui::End();
    }

    void Overlay::endFrame(SDL_Window* window) const {
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        SDL_GL_SwapWindow(window);
    }
}
