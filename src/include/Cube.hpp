#ifndef WORLD_IMAKER_CUBE_HPP 
#define WORLD_IMAKE_CUBE_HPP

class Cube
{
	protected:
		double m=_height;
		double m_width;
		double m_length;
		bool m_empty;

	public:
		// Builder
		Cube() = default;

		// Destroyer
		~Cube();

		// Getter
		inline double getHeight()const{ return m_height; };
		inline double getWidth()const{ return m_width; };
		inline double getLength()const{ return m_length; };
		inline double getEmpty()const{ return m_empty; };

		// Setter
		void setHeight(double height);
		void setWidth(double width);
		void setLength(double length);
		void setEmpty(bool empty);

		void display(glm::vec3 position,GLuint tex_id);
};

#endif // WORL_IMAKER_CUBE_HPP
