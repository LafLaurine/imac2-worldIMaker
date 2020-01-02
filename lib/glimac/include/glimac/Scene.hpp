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
			TrackballCamera camera;
			glm::mat4 MVMatrix, ProjMatrix, globalMVMatrix, cubeMVMatrix, NormalMatrix;
			glm::vec3 lightDir,lightIntensity, m_color;
		public:
			///default constructor of scene
			Scene() = default;
			///default destructor of scene
			~Scene() = default;
			///map between programtype and its program
			std::map<ProgramType, Program> m_programs;
			///attributes for uniform location
			GLuint uMVLocation,uMVPLocation, uLightLocation, uLightPointLocation,uAmbiantLight, uLightPosLocation, uColorLocation, uNormalMatLocation;
			GLuint uLuminosityLocation, uCubeTypeLocation;
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
			///get y position of directive light
			inline float getLightYD() {return yLightD;};
			///get z position of directive light
			inline float getLightZD() {return zLightD;};
			///get x position of point light
			inline float getLightXP() {return xLightP;};
			///get y position of point light
			inline float getLightYP() {return yLightP;};
			///get z position of point light
			inline float getLightZP() {return zLightP;};

			///get scene's cube
			inline std::vector<Cube>& getAllCubes() {return m_allCubes;};
			///load scene program (shaders)
			void loadProgram(ProgramType type, std::string vertexShader, std::string fragmentShader);
			///use program
			void useProgram(ProgramType type);
			///create uniform matrices for the scene
			void createUniformMatrices(ProgramType type);
			///calculate matrices for the camera
			void recalculateMatrices(TrackballCamera &camera, Cube cube);
			///initialize default scene
			void initAllCubes();
			///draw cube of default scene
			void drawCubes(TrackballCamera &camera, GLuint texId);
			///add light to the scene : directive light, point light and ambiant light
			void addLight();
			///set ground of the scene
			void setGround();
			///change luminosity of the scene
			void changeLuminosity(int dirLight, int pointLight);
			///change point light position
			void changePointLightPosition(float pointLightX, float pointLightY, float pointLightZ);
			///change directive light position
			void changeDirectiveLightPosition(float directiveLightX, float directiveLightY, float directiveLightZ);
			///transform 3D vector to 1D
			static unsigned int from3Dto1D(glm::ivec3 pos);
	};
}


#endif // WORLD_IMAKER_SCENE_HPP