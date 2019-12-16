#ifndef WORLD_IMAKER_SCENE_HPP 
#define WORLD_IMAKER_SCENE_HPP

#pragma once

#include <glimac/glm.hpp> 
#include <GL/glew.h>
#include <map>
#include <glimac/FreeFlyCamera.hpp>
#include <glimac/Program.hpp>
#include <glimac/Cube.hpp>
#include <vector>

namespace glimac
{
	
	class Scene
	{
		private:
			std::vector<Cube> m_all_cubes;
			FreeFlyCamera camera;
			GLuint uModelLocation;
			GLuint uViewProjLocation;
		public:
			std::map<ProgramType, Program> m_programs;
			Scene() = default;
			~Scene() = default;
			void loadProgram(ProgramType type, std::string vertexShader, std::string fragmentShader);
			void useProgram(ProgramType type);
			void create_uniform_matrices(ProgramType type);
			void drawCube(ProgramType cubeType);
			void recalculate_matrices(FreeFlyCamera camera, Cube cube);
			void initAllCubes();
			void drawCubes(FreeFlyCamera camera);
	};
}


#endif // WORLD_IMAKER_SCENE_HPP