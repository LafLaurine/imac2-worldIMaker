#ifndef GLIMAC_TEXTURE
#define GLIMAC_TEXTURE

#include <iostream>
#include <string>
#include <glimac/Image.hpp>
#include <GL/glew.h>

namespace glimac
{
	class Texture
	{
		private:
			std::string m_name;
			GLuint m_textureId;
			std::unique_ptr<Image> m_texturePointer;

		public:
			// Constructors
			Texture(){};
			Texture(std::string n);
			inline GLuint getId() const{return m_textureId;}

	};
}

#endif //GLIMAC_TEXTURE