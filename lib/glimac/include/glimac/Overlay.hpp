#ifndef GLIMAC_Overlay
#define GLIMAC_Overlay

#include <iostream>
#include <string>
#include <glm/glm.hpp>
#include <SDL2/SDL.h>
#include <glimac/Scene.hpp>
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
			void drawOverlay(Scene &scene);
    		void endFrame(SDL_Window* window) const;
			inline int getClickedReset(){return clickedReset;};
			inline int getClickedAddCube(){return clickedAddCube;};
			inline int getClickedDeleteCube(){return clickedDeleteCube;};
			inline int getClickedTree(){return clickedTree;};
			inline int getClickedCube(){return clickedCube;};
			inline int getClickedAddTexture(){return clickedAddTexture;};
			inline float* getColor(){return &m_myCol;};
		private:
			float m_myCol = 0.f;
			bool p_open;
			int clickedReset, clickedAddCube, clickedDeleteCube;
			int clickedTree, clickedCube, clickedAddTexture;
	};
}

#endif //GLIMAC_Overlay