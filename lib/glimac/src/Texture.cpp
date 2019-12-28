#include <iostream>
#include <string>
#include "glimac/Texture.hpp"
#include <GL/glew.h>

namespace glimac {
	Texture::Texture(std::string n, Scene &scene) {
		m_name = n;
		m_texturePointer = loadImage("./assets/textures/" + m_name);
		if(m_texturePointer == NULL)
		{
			std::cerr << "Couldn't load texture" << std::endl;
		}
		glGenTextures(1, &m_textureId);
		glBindTexture(GL_TEXTURE_2D, m_textureId);
		glTexImage2D(GL_TEXTURE_2D,  0,  GL_RGBA,  m_texturePointer->getWidth(),  m_texturePointer->getHeight(),  0,  GL_RGBA,  GL_FLOAT,  m_texturePointer->getPixels());
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glBindTexture(GL_TEXTURE_2D,  0);
    }

	void Texture::initTexture(Scene &scene) {
		glUniform1i(scene.uIsThereTexture, 1);
    }
}
