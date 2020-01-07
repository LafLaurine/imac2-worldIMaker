#ifndef WORLD_IMAKER_SCENE_HPP 
#define WORLD_IMAKER_SCENE_HPP

#pragma once
#include <map>
#include <glimac/FreeFlyCamera.hpp>
#include <glimac/Program.hpp>
#include <glimac/Cube.hpp>
#include <glimac/Texture.hpp>
#include <glimac/common.hpp>

namespace glimac
{
	
	class Scene
	{
		private:
			int pointLight;
			int directiveLight;
			float xLightD, yLightD, zLightD;
			float xLightP, yLightP, zLightP;
			std::list<Cube> m_allCubes;
			Cube m_cubeConstruct;
			FreeFlyCamera camera;
			glm::mat4 MVMatrix, ProjMatrix, globalMVMatrix, cubeMVMatrix, NormalMatrix;
			glm::vec3 lightDir,lightIntensity, m_color;
		public:
			///default constructor of scene
			Scene() = default;
			///default destructor of scene
			~Scene() = default;
   			///map between programtype and its program
			std::map<ProgramType, Program> m_programs;
			///3 tab of our world that contains cube
			Cube* tabCubes[m_width][m_height][m_length];
			///attributes for uniform location
			GLuint uMVLocation,uMVPLocation,uAmbiantLight, uLightPosLocation, uColorLocation, uNormalMatLocation;
			GLuint uLuminosityLocation, uCubeTypeLocation;
			GLuint uKs, uShininess, uLightDir_vs, uLightIntensityP, uLightIntensityD;
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
			inline std::list<Cube>& getAllCubes() {return m_allCubes;};
			///load scene program (shaders)
			void loadProgram(ProgramType type, std::string vertexShader, std::string fragmentShader);
			///use program
			void useProgram(ProgramType type);
			///unbind program
			void unbindProgram(ProgramType type);
			///create uniform matrices for the scene
			void createUniformMatrices(ProgramType type);
			///calculate matrices for the camera
			void calculateMatrices();
			///calculate matrices on change
			void recalculateMatrices(FreeFlyCamera &camera, Cube cube);
			///initialize default scene
			void initAllCubes();
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
			///change ambiant light intensity
			void changeIntensityAmbiant(float &x, float &y, float &z);
			///change directional light intensity
			void changeIntensityDirectional(float &x, float &y, float &z);
			///change point light intensity
			void changeIntensityPoint(float &x, float &y, float &z);

	};
}


#endif // WORLD_IMAKER_SCENE_HPP