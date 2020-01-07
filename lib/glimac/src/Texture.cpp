#include <iostream>
#include <string>
#include <glimac/Texture.hpp>
#include <glimac/gl-exception.hpp>
#include <GL/glew.h>

namespace glimac {
	
	//constructor texture
	Texture::Texture(std::string n) {
		m_name = n;
		//load image that we want
		m_texturePointer = loadImage("./assets/textures/" + m_name);
		assert(m_texturePointer && "Unable to load texture");

        //avoid memory leak
        if(glIsTexture(m_textureId) == GL_TRUE) glDeleteTextures(1, &m_textureId);
		
		//generate texture, bind it and associate all it needs
		GLCall(glGenTextures(1, &m_textureId));
		GLCall(glBindTexture(GL_TEXTURE_2D, m_textureId));
		GLCall(glTexImage2D(GL_TEXTURE_2D, 0,  GL_RGBA,  m_texturePointer->getWidth(),  m_texturePointer->getHeight(),  0,  GL_RGBA,  GL_FLOAT,  m_texturePointer->getPixels()));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
		GLCall(glBindTexture(GL_TEXTURE_2D, 0));
    }

}
