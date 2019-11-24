#include <glimac/glm.hpp> 
#include "glimac/Cube.hpp"

namespace glimac {
	
	Cube::Cube(): m_height(glm::vec3(0.f, 0.f, 0.f)),m_width(glm::vec3(0.f, 0.f, 0.f)), m_length(glm::vec3(0.f, 0.f, 0.f)), m_empty(true) {
	}    

	// Setter
	void Cube::setHeight(glm::vec3 height){
		glm::vec3 m_height = height;
	}
	void Cube::setWidth(glm::vec3 width){
		glm::vec3 m_width = width;
	}
	void Cube::setLength(glm::vec3 length){
		glm::vec3 m_length = length;
	}
	void Cube::setEmpty(bool empty){
		bool m_empty = empty;
	}
}