#ifndef WORLD_IMAKER_CUBE_HPP 
#define WORLD_IMAKER_CUBE_HPP

#pragma once
#include <glimac/glm.hpp> 
#include <GL/glew.h>

namespace glimac
{
	class Cube
	{
		private:
			GLuint m_vao;
			GLuint m_vbo;
			GLuint m_ibo;
			glm::vec3 m_position;
			glm::vec3 m_color;
		public:
			Cube();
			~Cube() = default;
			inline glm::vec3 getPosition(){ return m_position; };
			inline GLuint getVAO(){ return m_vao; };
			inline GLuint getIBO(){ return m_ibo; };
			inline float setPositionX(float positionX){return m_position.x = positionX;};
			inline float setPositionY(float positionY){return m_position.y = positionY;};
			inline float setPositionZ(float positionZ){return m_position.z = positionZ;};
			void initBuffer();
			void draw();
	};
}

#endif // WORLD_IMAKER_CUBE_HPP
