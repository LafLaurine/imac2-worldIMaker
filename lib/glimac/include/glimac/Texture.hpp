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
			std::string _name;
			GLuint _textureId;
			std::unique_ptr<Image> _texturePointer;

		public:
			// Constructors
			Texture(){};
			Texture(std::string n);
			inline GLuint getId() const{return _textureId;}

	};
}

#endif //GLIMAC_TEXTURE