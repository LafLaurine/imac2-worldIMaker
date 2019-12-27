#ifndef GLIMAC_TEXTURE
#define GLIMAC_TEXTURE

#include <iostream>
#include <string>
#include <glimac/Image.hpp>
#include <GL/glew.h>
#include <glimac/Cube.hpp>
#include <glimac/Scene.hpp>

namespace glimac
{
	class Texture
	{
		private:
			std::string m_name;
			
			std::unique_ptr<Image> m_texturePointer;

		public:
			// Constructors
			Texture(){};
			GLuint m_textureId;
			Texture(std::string n);
			inline GLuint getId() const{return m_textureId;}
			void initTexture(Cube &cube, Scene &scene);
	};
}
	

#endif //GLIMAC_TEXTURE