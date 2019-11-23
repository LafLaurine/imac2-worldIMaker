#ifndef WORLD_IMAKER_CUBE_HPP 
#define WORLD_IMAKE_CUBE_HPP

class Cube
{
	protected:
		double m_height;
		double m_width;
		double m_length;
		bool empty;

	public:
		// Builder
		Cube() = default;

		// Destroyer
		~Cube();

		// Getter
		inline double getHeight()const{ return m_height; };
		inline double getWidth()const{ return m_width; };
		inline double getLength()const{ return m_length; };

		// Setter
		void setHeight(Cube &cubeObj);
		void setWidth(Cube &cubeObj);
		void setLength(Cube &cubeObj);

		void display(glm::vec3 position,GLuint tex_id);
};

#endif // WORL_IMAKER_CUBE_HPP
