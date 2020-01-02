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
		private:
			float m_myCol = 0.f;
			bool p_open;
			int clickedReset, clickedAddCube, clickedDeleteCube;
			int clickedTree, clickedCube, clickedAddTexture, clickedChangeCamera,clickedRemoveTexture;
			ImGuiIO* m_io;

		public:
			///default constructor of overlay
			Overlay(){};
			///default destructor of overlay
			~Overlay();
			//getter
			inline const ImGuiIO* getIo(){return m_io;};
			///initialize Imgui window and context
			void initImgui(SDL_Window* window,SDL_GLContext* glContext);
			///open new frame of Imgui
			void beginFrame(SDL_Window* window) const;
			///draw Imgui window with its tools
			void drawOverlay(Scene &scene);
			///end frame of Imgui
    		void endFrame(SDL_Window* window) const;
			///get if user clicked reset button
			inline int getClickedReset(){return clickedReset;};
			///get if user clicked add cube button
			inline int getClickedAddCube(){return clickedAddCube;};
			///get if user clicked add delete cube button
			inline int getClickedDeleteCube(){return clickedDeleteCube;};
			///get if user clicked generate tree button
			inline int getClickedTree(){return clickedTree;};
			///get if user clicked generate big cube button
			inline int getClickedCube(){return clickedCube;};
			///get if user clicked add texture button
			inline int getClickedAddTexture(){return clickedAddTexture;};
			///get if user clicked remove texture button
			inline int getClickedRemoveTexture(){return clickedRemoveTexture;};
			///get if user clicked change camera
			inline int getClickedChangeCamera(){return clickedChangeCamera;};
			//get color of the color picker
			inline float* getColor(){return &m_myCol;};

			inline float setColor(float color){return m_myCol = color;};
	};
}

#endif //GLIMAC_Overlay