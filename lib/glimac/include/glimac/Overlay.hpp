#ifndef GLIMAC_Overlay
#define GLIMAC_Overlay

#include <iostream>
#include <string>
#include <glm/glm.hpp>
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_opengl3.h>
#include <imgui/imgui_impl_sdl.h>

namespace glimac
{
	class Overlay
	{
		public:
			// Constructor
			Overlay(){};
			//Destructor
			~Overlay();
			void initImgui(SDL_Window* window,SDL_GLContext* glContext) const;
			void beginFrame(SDL_Window* window) const;
			void drawOverlay();
    		void endFrame(SDL_Window* window) const;
			inline int getClickedAddCube(){return clickedAddCube;};
			inline int getClickedDeleteCube(){return clickedDeleteCube;};
			inline int getClickedDayCube(){return clickedDay;};
			inline int getClickedNightCube(){return clickedNight;};
			inline glm::vec4* getCurrentColor(){return current_color;};
		private:
			bool rouge=false;
			bool vert=false;
			bool bleu=false;

			std::string current_color_string="rouge";
			glm::vec4* current_color;
			bool p_open;
			int clickedAddCube;
			int clickedDeleteCube;
			int clickedDay;
			int clickedNight;
	};
}

#endif //GLIMAC_Overlay