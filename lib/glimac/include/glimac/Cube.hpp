#ifndef WORLD_IMAKER_CUBE_HPP 
#define WORLD_IMAKER_CUBE_HPP

#pragma once
#include <glimac/glm.hpp> 
#include <GL/glew.h>
#include <glimac/Image.hpp>

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
			bool m_invisible;
		public:
			Cube();
			Cube(glm::vec3 position);
			~Cube() = default;
			GLuint texId;
			inline glm::vec3 getPosition(){ return m_position; };
			inline GLuint getVAO(){ return m_vao; };
			inline GLuint getVBO(){ return m_vbo; };
			inline GLuint getIBO(){ return m_ibo; };
			inline bool getInvisible(){ return m_invisible; };
			inline glm::vec3 setPosition(glm::vec3 position){return m_position = position;};
			inline float setPositionX(float positionX){return m_position.x = positionX;};
			inline float setPositionY(float positionY){return m_position.y = positionY;};
			inline float setPositionZ(float positionZ){return m_position.z = positionZ;};
			inline bool setInvisible(const bool invisible){return m_invisible = invisible;}
			void initBuffer();
			void draw();
			void editColor(int type);
	};
}

#endif // WORLD_IMAKER_CUBE_HPP
