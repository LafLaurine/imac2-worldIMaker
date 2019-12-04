#ifndef WORLD_IMAKER_CUBE_HPP 
#define WORLD_IMAKER_CUBE_HPP

#pragma once
#include <glimac/glm.hpp> 
#include <GL/glew.h>

namespace glimac
{
	//actually, the position of the cube is due to its vertex
	class Cube
	{
		private:
			unsigned int m_vao;
			unsigned int m_ib;
		public:
			Cube(){};
			~Cube() = default;
			inline glm::vec3 getPosition()const{ return m_position; };
			void display();
			glm::vec3 m_position;

			//something inline to assign its shader maybe
	};
}

#endif // WORLD_IMAKER_CUBE_HPP
