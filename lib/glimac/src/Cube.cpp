#include "glimac/Cube.hpp"

namespace glimac {
	
	Cube::Cube(const GLint &shaderId, const GLint &type) :m_shaderId(shaderId), m_type(type) {
	}

	void Cube::draw() 
{
		// Bind
		GLCall(glBindVertexArray(m_vao));
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ib));
		m_shader.bind();

		// Update model mat uniform
		glm::mat4 modelMat = glm::translate(glm::mat4(1.0f), position);
		m_shader.setUniformMat4f("uModel", modelMat);

		// Draw call
		GLCall(glDrawElements(GL_TRIANGLES, std::size(cubeData::indices), GL_UNSIGNED_SHORT, (void*) 0));
	}

}