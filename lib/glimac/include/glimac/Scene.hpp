#ifndef WORLD_IMAKER_SCENE_HPP 
#define WORLD_IMAKER_SCENE_HPP

#pragma once

#include <glimac/glm.hpp> 
#include <GL/glew.h>
#include <glimac/Program.hpp>
#include <glimac/Cube.hpp>
#include <map>
#include <glimac/FreeFlyCamera.hpp>
#include <vector>

namespace glimac
{
	enum class ProgramType
	{
		FlatCube,
		TexturedCube,
	};

	class Scene
	{
		private:
			std::map<ProgramType, Program> m_programs;
			std::map<ProgramType, Cube> m_cubes;
			std::vector<Cube> m_all_cubes;
			FreeFlyCamera camera;
		public:
			Scene() = default;
			~Scene() = default;
			GLuint uMVPLocation;
			GLuint uMVLocation;
			GLuint uNormalLocation;
			void initAllCubes(unsigned int nb_cubes);
			void loadProgram(ProgramType type, std::string vertexShader, std::string fragmentShader);
			void useProgram(ProgramType type);
			void loadScene(ProgramType type);
    		void displayScene(ProgramType type);
			void moveCube(ProgramType cubeType);
			void drawCube(ProgramType cubeType);

	};
}


#endif // WORLD_IMAKER_SCENE_HPP