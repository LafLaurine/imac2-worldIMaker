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
			inline int getClickedSave(){return clickedSaveFile;};
			inline int getClickedDayCube(){return clickedDay;};
			inline int getClickedNightCube(){return clickedNight;};
			inline int getClickedChangeColor(){return clickedColor;}
			inline int getClickedRBF(){return clickedRBF;};
			inline float* getColor(){return &m_myCol;};
			inline void setColor(float color){m_myCol = color;};
		private:
			float m_myCol = 0.f;
			bool p_open;
			int clickedAddCube, clickedDeleteCube;
			int clickedDay, clickedNight;
			int clickedSaveFile, clickedLoadFile;
			int clickedColor;
			int clickedRBF;
	};
}

#endif //GLIMAC_Overlay