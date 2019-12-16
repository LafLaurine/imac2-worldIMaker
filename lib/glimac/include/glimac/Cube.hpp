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
			GLuint m_vao;
			GLuint m_ibo;
		public:
			Cube();
			~Cube() = default;
			glm::vec3 m_position;
			inline glm::vec3 getPosition()const{ return m_position; };
			void initBuffer();
			void initCube();
			void draw();

			//something inline to assign its shader maybe
	};
}

#endif // WORLD_IMAKER_CUBE_HPP
