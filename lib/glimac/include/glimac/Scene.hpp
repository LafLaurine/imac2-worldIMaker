#ifndef WORLD_IMAKER_SCENE_HPP 
#define WORLD_IMAKER_SCENE_HPP

#pragma once

#include <glimac/glm.hpp> 
#include <GL/glew.h>
#include <glimac/Program.hpp>
#include <glimac/Cube.hpp>
#include <map>

namespace glimac
{
	enum class ProgramType
	{
		FlatCube,
		TexturedCube,
	};

	enum class CubeType
	{
		FlatCube,
		TexturedCube,
	};

	class Scene
	{
		private:
			std::map<ProgramType, Program> m_programs;
			std::map<CubeType, Cube> m_cubes;
		public:
			Scene() = default;
			~Scene() = default;
			GLuint uMVPLocation;
			GLuint uMVLocation;
			void loadProgram(ProgramType type, std::string vertexShader, std::string fragmentShader);
			void useProgram(ProgramType type);
			void loadTexture(ProgramType type);

	};
}


#endif // WORLD_IMAKER_SCENE_HPP