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
			std::map<ProgramType, Program> m_programs;
			FreeFlyCamera camera;
			glm::mat4 MV, ProjMatrix;
		public:
			Scene() = default;
			~Scene() = default;

			GLuint uModelLocation;
			GLuint uViewProjLocation;
			GLuint uTexLocation;
			GLuint uNormalLocation;
			inline std::vector<Cube> getAllCubes(){ return m_all_cubes; };
			void loadProgram(ProgramType type, std::string vertexShader, std::string fragmentShader);
			void useProgram(ProgramType type);
			void create_uniform_matrices(ProgramType type);
			void drawCube(ProgramType cubeType);
			void recalculate_matrices(FreeFlyCamera &camera, Cube cube);
			void initAllCubes(unsigned int nb_cubes);
			void drawCubes(FreeFlyCamera &camera);
			void moveCubesLeft();
			void moveCubesRight();
			void moveCubesUp();
			void moveCubesDown();
	};
}


#endif // WORLD_IMAKER_SCENE_HPP