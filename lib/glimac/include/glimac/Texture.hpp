#ifndef GLIMAC_TEXTURE
#define GLIMAC_TEXTURE

#include <iostream>
#include <string>
#include <glimac/Image.hpp>
#include <GL/glew.h>
#include <glimac/Scene.hpp>

namespace glimac
{
	class Texture
	{
		private:
			std::string m_name;
			std::unique_ptr<Image> m_texturePointer;

		public:
			///default constructor of texture
			Texture(){};
			///texture constructor with name of the texture and the scene concerned precised
			Texture(std::string n);
			GLuint m_textureId;
			///get the id of the texture
			inline GLuint getId() const{return m_textureId;}
			///initialize texture
			void initTexture(Scene &scene);
			void unbindTexture(Scene &scene);
	};
	void displayFull(GLuint* gameStart);
}
	

#endif //GLIMAC_TEXTURE