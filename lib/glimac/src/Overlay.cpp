#include "glimac/Overlay.hpp"
#include <iostream>

#include <imgui/imgui.h>
#include <imgui/imgui_stdlib.h>
#include <glimac/File.hpp>
#include <list>
#include <algorithm>

namespace glimac {

    Overlay::~Overlay() {
        delete m_io;
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplSDL2_Shutdown();
        ImGui::DestroyContext();
    }

    void Overlay::initImgui(SDL_Window* window,SDL_GLContext* glContext)  {
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
        ImGui::Begin("Cube tools",&p_open);
        {
            ImGui::ColorEdit4("Color", (float*)&i_color);
            m_myCol = glm::vec4(i_color.x, i_color.y, i_color.z, 1.0);

            //set clicked variables to communicate with the main
            clickedAddCube = 0;
            clickedDeleteCube = 0;
            clickedRBF = 0;
            clickedCube = 0;
            clickedReset = 0;
            clickedAddTexture = 0;

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

            if (ImGui::Button("Remove texture")) 
            {
                clickedRemoveTexture++;
            }

            if (ImGui::Button("Destroy cube")) 
            { 
                clickedDeleteCube++;
            }
            
            if (ImGui::Button("Set ground")) 
            {
                scene.setGround();
            }

            if (ImGui::Button("Generate rbf1")) 
            {
                clickedRBF++;
            }

            if (ImGui::Button("Generate rbf2")) 
            {
               clickedCube++;
            }

        }
        ImGui::End();

        //set the save and load window
        ImGui::Begin("Save and load",&p_open);
        {
            //set strings for save and load filepath and filename
            static char filepath[128] = "";
            static char filename[128] = "";
            ImGui::Text("Save file :");
            ImGui::InputTextWithHint("filepath", "enter file path", filepath, sizeof(filepath), ImGuiInputTextFlags_EnterReturnsTrue);
            ImGui::InputTextWithHint("filename", "enter file name", filename, sizeof(filename), ImGuiInputTextFlags_EnterReturnsTrue);
            std::string filePathS(filepath);
            std::string fileNameS(filename);
            if (ImGui::Button("Save"))
            {
                //save file with filepath and filename of the user choice
                saveFile(filePathS,fileNameS,scene.getAllCubes(),scene);
            }

            static char filepathLoad[128] = "";
            static char filenameLoad[128] = "";
            ImGui::Text("Load file :");
            ImGui::InputTextWithHint("filepathLoad", "enter file path", filepathLoad, sizeof(filepath), ImGuiInputTextFlags_EnterReturnsTrue);
            ImGui::InputTextWithHint("filenameLoad", "enter file name", filenameLoad, sizeof(filename), ImGuiInputTextFlags_EnterReturnsTrue);
            std::string filePathL(filepathLoad);
            std::string fileNameL(filenameLoad);

            if (ImGui::Button("Load"))
            {
                //load file with filepath and filename of the user choice
                loadFile(filePathL, fileNameL, scene.getAllCubes(),scene);
            }
        }
        ImGui::End();
        
        ImGui::Begin("Light intensity",&p_open); {
            ImGui::Text("Directional light intensity :");
            static float l1=2.0f;
            ImGui::SliderFloat("intensity d", &l1, 0.0f, 10.0f);
            scene.changeIntensityDirectional(l1,l1,l1);

            ImGui::Text("Point light intensity :");
            static float x1=2.0f;
            ImGui::SliderFloat("intensity p", &x1, 0.0f, 10.0f);
            scene.changeIntensityPoint(x1,x1,x1);

            //ambiant light intensity
            ImGui::Text("Ambiant light intensity :");
            static float f1=0.2f;
            ImGui::SliderFloat("intensity a", &f1, 0.0f, 1.0f);
            scene.changeIntensityAmbiant(f1,f1,f1);

            if(ImGui::Button("Night")) {
                f1 = 0.47f;
                scene.changeIntensityAmbiant(f1,f1,f1);
            }
            if (ImGui::Button("Day")) {
                f1 = 0.2f;
                scene.changeIntensityAmbiant(f1,f1,f1);
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