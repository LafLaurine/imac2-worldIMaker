#ifndef WORLD_IMAKER_SCENE_HPP 
#define WORLD_IMAKER_SCENE_HPP

#pragma once

#include <glimac/glm.hpp> 
#include <GL/glew.h>
#include <map>
#include <glimac/TrackballCamera.hpp>
#include <glimac/Program.hpp>
#include <glimac/Cube.hpp>
#include <vector>


namespace glimac
{
	
	class Scene
	{
		private:
			static const unsigned int m_height = 20;
			static const unsigned int m_width = 20;
			static const unsigned int m_length = 20;
			int pointLight;
			int directiveLight;
			float xLightD, yLightD, zLightD;
			float xLightP, yLightP, zLightP;
			std::vector<Cube> m_allCubes;
			std::map<ProgramType, Program> m_programs;
			TrackballCamera camera;
			glm::mat4 MVMatrix, ProjMatrix, globalMVMatrix, cubeMVMatrix, NormalMatrix;
			glm::vec3 lightDir,lightIntensity, m_color;
		public:
			///default constructor
			Scene() = default;
			///default destructor
			~Scene() = default;

			GLuint uMVLocation,uMVPLocation, uLightLocation, uLightPointLocation, uLightPosLocation, uColorLocation, uNormalMatLocation;
			GLuint uLuminosityLocation;
			GLuint uKd, uKs, uShininess, uLightDir_vs, uLightIntensityP, uLightIntensityD;
			GLuint uTextureLocation, uIsThereTexture;
			///get scene's height
			inline int getHeight(){ return m_height; };
			///get scene's width
			inline int getWidth(){ return m_width; };
			///get scene's length
			inline int getLength(){ return m_length; };
			///check if there is a point light
			inline int getPointLight() {return pointLight;};
			///check if there is a directive light
			inline int getDirectiveLight() {return directiveLight;};
			///get x position of directive light
			inline float getLightXD() {return xLightD;};
			inline float getLightYD() {return yLightD;};
			inline float getLightZD() {return zLightD;};
			inline float getLightXP() {return xLightP;};
			inline float getLightYP() {return yLightP;};
			inline float getLightZP() {return zLightP;};

			//get scene's cube
			inline std::vector<Cube>& getAllCubes() {return m_allCubes;};
			//load scene program (shaders)
			void loadProgram(ProgramType type, std::string vertexShader, std::string fragmentShader);
			//use program
			void useProgram(ProgramType type);
			//create uniform matrices for the scene
			void create_uniform_matrices(ProgramType type);
			//calculate matrices for the camera
			void recalculate_matrices(TrackballCamera &camera, Cube cube);
			void initAllCubes();
			void drawCubes(TrackballCamera &camera, GLuint texId);
			void addLight();
			void setGround();
			//change luminosity of the scene
			void changeLuminosity(int dirLight, int pointLight);
			void changePointLightPosition(float pointLightX, float pointLightY, float pointLightZ);
			void changeDirectiveLightPosition(float directiveLightX, float directiveLightY, float directiveLightZ);
			//transform 1D vector to 3D
			static unsigned int from1Dto3D(glm::ivec3 pos);
	};
}


#endif // WORLD_IMAKER_SCENE_HPP