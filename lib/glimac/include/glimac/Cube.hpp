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
			glm::vec3 m_position;
			glm::vec3 m_normal;
			GLint m_shaderId;
        	GLint m_type; // in the subject, it is said that color = different cube type

		public:
			// Builder
			Cube(const GLint &shaderId, const GLint &type);

			// Destroyer
			~Cube() = default;
			void setPosition(glm::vec3 position);
			inline glm::vec3 getPosition()const{ return m_position; };
			void display();

			//something inline to assign its shader maybe
	};
}

#endif // WORLD_IMAKER_CUBE_HPP
