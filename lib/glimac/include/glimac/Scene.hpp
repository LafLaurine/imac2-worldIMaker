#ifndef WORLD_IMAKER_SCENE_HPP 
#define WORLD_IMAKER_SCENE_HPP

#pragma once

#include <glimac/glm.hpp> 
#include <GL/glew.h>
#include <glimac/Cube.hpp>
#include <glimac/FreeFlyCamera.hpp> 
#include <imgui/imgui.h>
#include <imgui/imgui_impl_opengl3.h>
#include <imgui/imgui_impl_sdl.h>

namespace glimac
{
	class Scene
	{
		private:
			Cube cube1;
			Cube cube2;
			Cube cube3;
			
			
		public:
			Scene() = default;
			~Scene() = default;
			void displayScene();
	};
}


#endif // WORLD_IMAKER_SCENE_HPP