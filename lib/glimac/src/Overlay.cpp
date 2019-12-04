#include "glimac/Overlay.hpp"
#include <iostream>

namespace glimac {
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

    void Overlay::drawOverlay() const {
        ImGui::Begin("Main debug window");
        {
            static float f = 0.0f;
            float col = 0.f;
            int show = 1;
            ImGui::Text(u8"Hello, world! ");
            ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
            ImGui::ColorEdit3("clear color", (float*)&col);
            if (ImGui::Button("Test Window")) show ^= 1;
            if (ImGui::Button("Another Window")) show ^= 1;
        }
        ImVec2 v = ImGui::GetWindowSize();  // v = {32, 48} ,   is tool small
        ImGui::Text("%f %f", v.x, v.y);
        if (ImGui::GetFrameCount() < 10)
            printf("Frame %d: Size %f %f\n", ImGui::GetFrameCount(), v.x, v.y);
        ImGui::End();
    }

    void Overlay::endFrame(SDL_Window* window) const {
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        SDL_GL_SwapWindow(window);
    }
}
