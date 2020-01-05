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
			std::unique_ptr<Image> m_texturePointer;
			GLuint m_textureId;
		public:
			///default constructor of texture
			Texture(){};
			///texture constructor with name of the texture and the scene concerned precised
			Texture(std::string n);
			~Texture() = default;
			///get the id of the texture
			inline GLuint getId() const{return m_textureId;}
			void bind(unsigned int slot) const;
			void unbind(unsigned int slot) const;
	};
}
	

#endif //GLIMAC_TEXTURE