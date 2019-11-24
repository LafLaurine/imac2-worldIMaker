#ifndef WORLD_IMAKER_CUBE_HPP 
#define WORLD_IMAKER_CUBE_HPP


namespace glimac
{
	//actually, the position of the cube is due to its vertex
	class Cube
	{
		private:
			glm::vec3 m_position;
			glm::vec3 m_normal;
			GLuint m_shaderId;
        	GLuint m_type; // in the subject, it is said that color = different cube type

		public:
			// Builder
			Cube(const GLint &shaderId, const GLint &type);

			// Destroyer
			~Cube() = default;
			void Cube::setPosition(glm::vec3 position){

			void display();

			//something inline to assign its shader maybe
	};
}

#endif // WORLD_IMAKER_CUBE_HPP
