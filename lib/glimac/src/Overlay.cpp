#include "glimac/Overlay.hpp"
#include <iostream>

namespace glimac {
    
    void Overlay::initImgui(SDL_Window* window,SDL_GLContext glContext) const {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGui::StyleColorsDark();
        ImGui_ImplSDL2_InitForOpenGL(window,glContext);
        ImGui_ImplOpenGL3_Init("#version 330 core");
    }
    
    void Overlay::beginFrame(SDL_Window* window) const {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame(window);
        ImGui::NewFrame();
    }

    void Overlay::drawOverlay() const {
        ImGui::Begin("Main debug window");
            ImGui::Text("Hello world");
        ImGui::End();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    void Overlay::endFrame(SDL_Window* window,SDL_GLContext glContext) const {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplSDL2_Shutdown();
        ImGui::DestroyContext();
        SDL_GL_DeleteContext(glContext);
        SDL_DestroyWindow(window);
    }
}
