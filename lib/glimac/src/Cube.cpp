#include "glimac/Cube.hpp"

namespace glimac {
	
	Cube::Cube(const GLint &shaderId, const GLint &type) :m_shaderId(shaderId), m_type(type) {
	}

	// Setter
	void Cube::setPosition(glm::vec3 position){
		glm::vec3 m_position = position;
	}
}