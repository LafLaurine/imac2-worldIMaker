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
            ImGui::ColorEdit4("Color", this->getColor());
            clickedAddCube = 0;
            clickedDeleteCube = 0;
            clickedDay = 0;
            clickedNight = 0;
            clickedSaveFile = 0;
            clickedLoadFile = 0;
            clickedRBF = 0;
            clickedReset = 0;
            clickedSetGround = 0;

            if (ImGui::Button("Reset")) 
            {
                clickedReset++;
            }

            if (ImGui::Button("Add cube")) {
                clickedAddCube++;
            }
            
            if (ImGui::Button("Add texture")) 
            {
            }
            if (ImGui::Button("Destroy cube")) 
            { 
                clickedDeleteCube++;
            }
            
            if (ImGui::Button("Set ground")) 
            {
                scene.setGround();
            }


            if (ImGui::Button("Generate scene")) 
            {
                clickedRBF++;
            }
        }
        ImGui::End();
        ImGui::Begin("Save and load",&p_open);
        {
            static std::string filePath = "./assets/doc/";
            static std::string filename = "world.txt";

            static std::string loadFilePath = "./assets/doc/";
            static std::string loadFilename = "world.txt";
            ImGui::Text("Save file :");
            ImGui::InputText("Path", &filePath);
            ImGui::InputText("Filename", &filename);
            if (ImGui::Button("Save"))
            {
                saveFile(filePath,filename,scene.getAllCubes());
            }

            ImGui::Text("Load file :");
            ImGui::InputText("Path", &loadFilePath);
            ImGui::InputText("Filename", &loadFilename);

            if (ImGui::Button("Load"))
            {
                loadFile(filePath, loadFilename, scene.getAllCubes());
            }
        }
        ImGui::End();
        ImGui::Begin("Light",&p_open); {
            static int dirLight = scene.getDirectiveLight();
            static float dirLightX = scene.getLightXD();
            static float dirLightY = scene.getLightYD();
            static float dirLightZ = scene.getLightZD();

            static int pointLight = scene.getPointLight();
            static float pointLightX = scene.getLightXP();
            static float pointLightY = scene.getLightYP();
            static float pointLightZ = scene.getLightZP();

            const char* itemsLight[] = { "On", "Off"};
            ImGui::Text("Lumiere directionnelle :");
            ImGui::Combo("D", &dirLight, itemsLight, IM_ARRAYSIZE(itemsLight));
            ImGui::Text("Coordinates D");
            ImGui::InputFloat("xD",&dirLightX);
            ImGui::Text("Y :");
            ImGui::InputFloat("yD", &dirLightY);
            ImGui::Text("Z :");
            ImGui::InputFloat("zD", &dirLightZ);

            // Spotlight
            ImGui::Text("Lumiere ponctuelle :");
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
