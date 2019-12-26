#include "glimac/Overlay.hpp"
#include <iostream>

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
        ImGui::Begin("WorldIMaker tools",&p_open,ImGuiWindowFlags_NoMove | ImGuiWindowFlags_MenuBar  |ImGuiWindowFlags_NoCollapse);
        {
            ImGui::ColorEdit4("Color", this->getColor());

            int show = 1;
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
                show ^= 1;
                clickedReset++;
            }

            if (ImGui::Button("Add cube")) {
                show ^= 1;
                clickedAddCube++;
            }
            
            if (ImGui::Button("Add texture")) 
            {
                show ^= 1;
            }
            if (ImGui::Button("Destroy cube")) 
            { 
                show ^= 1;
                clickedDeleteCube++;
            }

            if (ImGui::Button("Save"))
            {
                show ^= 1;
                clickedSaveFile++;
            }

            if (ImGui::Button("Load"))
            {
                show ^= 1;
                clickedLoadFile++;
            }
            
            if (ImGui::Button("Set ground")) 
            {
                show ^= 1;
                clickedSetGround++;
            }


            if (ImGui::Button("Generate scene")) 
            {
                show ^= 1;
                clickedRBF++;
            }
        }
        ImGui::End();
        ImGui::Begin("Light tools",&p_open); {
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
