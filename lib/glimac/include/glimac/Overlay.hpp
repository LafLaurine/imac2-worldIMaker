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
			bool p_open;
			int clickedReset, clickedAddCube, clickedDeleteCube;
			int clickedRBF, clickedPig, clickedCube, clickedAddTextureIron, clickedAddTextureWood,clickedAddTextureGrass,clickedAddTextureGold,clickedAddTextureGround,clickedRemoveTexture;
			ImGuiIO* m_io;
			ImVec4 i_color;
			glm::vec4 m_myCol;

		public:
			///default constructor of overlay
			Overlay(){};
			///default destructor of overlay
			~Overlay();
			//getter of io
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
			inline int getClickedRBF(){return clickedRBF;};
			///get if user clicked generate big cube button
			inline int getClickedCube(){return clickedCube;};
			///get if user clicked add texture button
			inline int getClickedAddTextureWood(){return clickedAddTextureWood;};
			inline int getClickedAddTextureGround(){return clickedAddTextureGround;};
			inline int getClickedAddTextureGold(){return clickedAddTextureGold;};
			inline int getClickedAddTextureIron(){return clickedAddTextureIron;};
			inline int getClickedAddTextureGrass(){return clickedAddTextureGrass;};
			inline int getClickedAddTexturePig(){return clickedPig;};
			///get if user clicked remove texture button
			inline int getClickedRemoveTexture(){return clickedRemoveTexture;};
			//get color of the color picker
			inline glm::vec4* getColor(){return &m_myCol;};
	};
}

#endif //GLIMAC_Overlay