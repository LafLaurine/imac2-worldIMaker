#ifndef WORLD_IMAKER_CUBE_HPP 
#define WORLD_IMAKER_CUBE_HPP

#pragma once
#include <glimac/glm.hpp> 
#include <GL/glew.h>
#include <glimac/Image.hpp>
#include <glimac/CubeData.hpp>

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
			glm::ivec3 m_position;
			glm::vec4 m_color;
			bool m_visible;
		public:
			int m_type;
			///default constructor of cube
			Cube();
			///constructor with a specific position set
			Cube(glm::ivec3 position);
			///default destructor of cube
			~Cube() = default;
			///initialize cube buffer
			void initBuffer();
			///get cube position
			inline glm::ivec3 getPosition(){ return m_position; };
			///get cube VAO
			inline GLuint getVAO(){ return m_vao; };
			///get cube VBO
			inline GLuint getVBO(){ return m_vbo; };
			///get cube IBO
			inline GLuint getIBO(){ return m_ibo; };
			///check if cube is visible
			inline bool isVisible(){ return m_visible; };
			///set position of the cube
			inline glm::ivec3 setPosition(glm::ivec3 position){ return m_position = position;};
			///set X position of the cube
			inline int setPositionX(int positionX){return m_position.x = positionX;};
			///set Y position of the cube
			inline int setPositionY(int positionY){return m_position.y = positionY;};
			///set Z position of the cube
			inline int setPositionZ(int positionZ){return m_position.z = positionZ;};
			///get cube color
			inline glm::vec4 getColor() {return m_color;};
			///set cube color
			inline void setColor(glm::vec4 colorSend){m_color = colorSend;};
			///set cube visible
			void setVisible();
			///set cube invisible
			void setInvisible();
			///draw a cube
			void draw(GLuint textureId);
			bool operator==(Cube cube);
	};
}

#endif // WORLD_IMAKER_CUBE_HPP
