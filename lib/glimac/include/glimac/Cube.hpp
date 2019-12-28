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
		///attributes are set protected because the class cursor inherit of cube
		protected:
			GLuint m_vao;
			GLuint m_vbo;
			GLuint m_ibo;
			GLuint texId;
			glm::vec3 m_position;
			glm::vec3 m_color;
			bool m_visible;
		public:
			int m_type;
			///default constructor of cube
			Cube();
			///constructor with a specific position set
			Cube(glm::vec3 position);
			///default destructor of cube
			~Cube() = default;
			///initialize cube buffer
			void initBuffer();
			///get cube position
			inline glm::vec3 getPosition(){ return m_position; };
			///get cube VAO
			inline GLuint getVAO(){ return m_vao; };
			///get cube VBO
			inline GLuint getVBO(){ return m_vbo; };
			///get cube IBO
			inline GLuint getIBO(){ return m_ibo; };
			///check if cube is visible
			inline bool isVisible(){ return m_visible; };
			///set position of the cube
			inline glm::vec3 setPosition(glm::vec3 position){return m_position = position;};
			///set X position of the cube
			inline float setPositionX(float positionX){return m_position.x = positionX;};
			///set Y position of the cube
			inline float setPositionY(float positionY){return m_position.y = positionY;};
			///set Z position of the cube
			inline float setPositionZ(float positionZ){return m_position.z = positionZ;};
			///get cube color
			inline glm::vec3 getColor() {return m_color;};
			///set cube color
			inline void setColor(glm::vec3 colorSend){m_color = colorSend;};
			///set cube visible
			void setVisible();
			///set cube invisible
			void setInvisible();
			///draw a cube
			void draw(GLuint textureId);
	};
}

#endif // WORLD_IMAKER_CUBE_HPP
