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
		protected:
			GLuint m_vao;
			GLuint m_vbo;
			GLuint m_ibo;
			glm::vec3 m_position;
			glm::vec3 m_color;
			bool m_visible;
			bool m_selected;
		public:
			Cube();
			Cube(glm::vec3 position);
			~Cube() = default;
			GLuint texId;
			inline glm::vec3 getPosition(){ return m_position; };
			inline GLuint getVAO(){ return m_vao; };
			inline GLuint getVBO(){ return m_vbo; };
			inline GLuint getIBO(){ return m_ibo; };
			inline bool isVisible(){ return m_visible; };
			inline bool isSelected(){ return m_selected; };
			inline glm::vec3 setPosition(glm::vec3 position){return m_position = position;};
			inline float setPositionX(float positionX){return m_position.x = positionX;};
			inline float setPositionY(float positionY){return m_position.y = positionY;};
			inline float setPositionZ(float positionZ){return m_position.z = positionZ;};
			inline glm::vec3 getColor() {return m_color;};
			inline void setColor(glm::vec3 colorSend){m_color = colorSend;};
			void setVisible();
			void setInvisible();
			void initBuffer();
			void draw();
			void update();
			void setSelected();
			void unselect();
	};
}

#endif // WORLD_IMAKER_CUBE_HPP
