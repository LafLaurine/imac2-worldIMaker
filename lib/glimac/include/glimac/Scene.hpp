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
			/*std::map<ProgramType, Cube> m_cubes;
			std::vector<Cube> m_all_cubes;
			FreeFlyCamera camera;

			GLuint uMVPLocation;
			GLuint uMVLocation;
			GLuint uNormalLocation;*/
		public:
			std::map<ProgramType, Program> m_programs;
			Scene() = default;
			~Scene() = default;
			//void initAllCubes(unsigned int nb_cubes);
			void loadProgram(ProgramType type, std::string vertexShader, std::string fragmentShader);
			void useProgram(ProgramType type);
			/*void loadScene(ProgramType type);
    		void displayScene(ProgramType type);
			void moveCube(ProgramType cubeType);
			void drawCube(ProgramType cubeType);*/
	};
}


#endif // WORLD_IMAKER_SCENE_HPP