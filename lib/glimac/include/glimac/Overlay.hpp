#ifndef GLIMAC_Overlay
#define GLIMAC_Overlay

#include <iostream>
#include <string>
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
		private:
			bool p_open;
			int clickedAddCube;
			int clickedDeleteCube;
	};
}

#endif //GLIMAC_Overlay