#ifndef WORLD_IMAKER_CUBE_HPP 
#define WORLD_IMAKER_CUBE_HPP

#pragma once
#include <glimac/glm.hpp> 
#include <map>
#include <glimac/Program.hpp>
#include <GL/glew.h>
#include <glimac/FreeFlyCamera.hpp>

namespace glimac
{
	class Vertex3DColor
	{    
	public:
		glm::vec3 m_position;
		glm::vec3 m_color;
		Vertex3DColor();
		Vertex3DColor(glm::vec3 position, glm::vec3 color)
			:m_position(position), m_color(color) {}
	};

	//actually, the position of the cube is due to its vertex
	class Cube
	{
		private:
			GLuint m_vao;
			GLuint m_ibo;
			GLuint m_vbo;
			glm::vec3 m_position;
			glm::vec3 m_color;
			FreeFlyCamera camera;	
	
		public:

			GLuint uMVPLocation;
			GLuint uMVLocation;
			GLuint uNormalLocation;	
		  	Cube();
    		Cube(glm::vec3 position, glm::vec3 color);
			~Cube();
			inline glm::vec3 getPosition(){ return m_position; };
			inline glm::vec3 getColor(){ return m_color; };
			inline GLuint getVAO(){ return m_vao; };
			inline GLuint getIBO(){ return m_ibo; };
			inline float setPositionX(float positionX){return m_position.x = positionX;};
			inline float setPositionY(float positionY){return m_position.y = positionY;};
			inline float setPositionZ(float positionZ){return m_position.z = positionZ;};
			void create_uniform_matrices(Program &program);
			void initBuffer();
			void draw();
	};
};

#endif // WORLD_IMAKER_CUBE_HPP
