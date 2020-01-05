#include <iostream>
#include <string>
#include <glimac/Texture.hpp>
#include <glimac/gl-exception.hpp>
#include <GL/glew.h>

namespace glimac {
	
	Texture::Texture(std::string n) {
		m_name = n;
		m_texturePointer = loadImage("./assets/textures/" + m_name);
		if(!m_texturePointer)
		{
			std::cerr << "Couldn't load texture" << std::endl;
			exit(EXIT_FAILURE);
		}

        //Avoid memory leak
        if(glIsTexture(m_textureId) == GL_TRUE) glDeleteTextures(1, &m_textureId);
		
		GLCall(glGenTextures(1, &m_textureId));
		GLCall(glBindTexture(GL_TEXTURE_2D, m_textureId));
		GLCall(glTexImage2D(GL_TEXTURE_2D, 0,  GL_RGBA,  m_texturePointer->getWidth(),  m_texturePointer->getHeight(),  0,  GL_RGBA,  GL_FLOAT,  m_texturePointer->getPixels()));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
		GLCall(glBindTexture(GL_TEXTURE_2D, 0));
    }

	void Texture::bind(unsigned int slot) const{
		glActiveTexture(GL_TEXTURE+slot);
		glBindTexture(GL_TEXTURE_2D, m_textureId);
	}

	void Texture::unbind(unsigned int slot) const{
		glActiveTexture(GL_TEXTURE+slot);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

}
