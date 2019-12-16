#ifndef WORLD_IMAKER_SCENE_HPP 
#define WORLD_IMAKER_SCENE_HPP

#pragma once

#include <glimac/glm.hpp> 
#include <GL/glew.h>
#include <map>
#include <glimac/Program.hpp>
#include <glimac/Cube.hpp>
#include <vector>
#include <eigen3/Eigen/Dense>

namespace glimac
{
	
	class Scene
	{
		private:
			static const unsigned int m_width = 3;
			static const unsigned int m_length = 3;
			static const unsigned int m_height = 3;
    		static const unsigned int m_max_cubes_in_column = 10;
			Eigen::Matrix <std::vector<Cube>, m_length, m_width> m_all_cubes;
			std::map<ProgramType, Program> m_programs;
			//std::vector<Cube> m_all_cubes;
		public:
			Scene() = default;
			~Scene() = default;
			void loadProgram(ProgramType type, std::string vertexShader, std::string fragmentShader);
			void useProgram(ProgramType type);
			void initAllCubes();
			void renderAll(ProgramType type);
			inline Eigen::Matrix <std::vector<Cube>, m_length, m_width> get_cubes() { return m_all_cubes; }
			inline unsigned int get_width() const { return m_width; } 
			inline unsigned int get_length() const { return m_length; }
			inline unsigned int get_height() const { return m_height; }
	};
}


#endif // WORLD_IMAKER_SCENE_HPP