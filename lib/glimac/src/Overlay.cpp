#include "glimac/Overlay.hpp"
#include <iostream>

#include <imgui/imgui.h>
#include <imgui/imgui_stdlib.h>
#include <glimac/File.hpp>

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

        m_io = new ImGuiIO();
        *m_io = ImGui::GetIO();
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
            //set color picker
            static float color;
            ImGui::ColorEdit4("Color", &color);
            glm::vec4 goodColor = glm::make_vec4(&color);
            setColor(goodColor);

            //set clicked variables to communicate with the main
            clickedAddCube = 0;
            clickedDeleteCube = 0;
            clickedTree = 0;
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

            if (ImGui::Button("Generate tree")) 
            {
                clickedTree++;
            }

            if (ImGui::Button("Generate big cube")) 
            {
               clickedCube++;
            }

            // Texture
         /*   const char* itemsTextures[] = { "groundTree", "tree"};
            int item_currentTexture = scene.tex->getId();
            ImGui::Text("Texture:");
            ImGui::Combo("Texture", &item_currentTexture, itemsTextures, IM_ARRAYSIZE(itemsTextures));*/
        }
        ImGui::End();

        //set the save and load window
        ImGui::Begin("Save and load",&p_open);
        {
            //set strings for save and load filepath and filename
            std::string filePath = "./assets/doc/";
            std::string filename = "world.txt";
            ImGui::Text("Save file :");
            ImGui::InputText("Save path", &filePath);
            ImGui::InputText("Save filename", &filename);
            if (ImGui::Button("Save"))
            {
                //save file with filepath and filename of the user choice
                saveFile(filePath,filename,scene.getAllCubes());
            }

            std::string loadFilePath = "./assets/doc/";
            std::string loadFilename = "world.txt";
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
