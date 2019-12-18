#ifndef WORLD_IMAKER_SCENE_HPP 
#define WORLD_IMAKER_SCENE_HPP

#pragma once

#include <glimac/glm.hpp> 
#include <GL/glew.h>
#include <map>
#include <glimac/FreeFlyCamera.hpp>
#include <glimac/Program.hpp>
#include <glimac/Cube.hpp>
#include <vector>

namespace glimac
{
	
	class Scene
	{
		private:
			std::vector<Cube> m_all_cubes;
			std::map<ProgramType, Program> m_programs;
			FreeFlyCamera camera;
			glm::mat4 MVMatrix, ProjMatrix, NormalMatrix;
			glm::vec3 Kd,Ks,lightDir,lightIntensity;
			int m_height;
			int m_width;
			int m_length;
		public:
			Scene() = default;
			Scene(int height, int width, int len);
			~Scene() = default;

			GLuint uModelLocation,uViewProjLocation, uTexLocation, uNormalMatLocation;
			GLuint uKd,uKs,uShininess,uLightDir_vs, uLightIntensity;
			inline int getHeight(){ return m_height; };
			inline int getWidth(){ return m_width; };
			inline int getLength(){ return m_length; };
			inline std::vector<Cube> getAllCubes(){ return m_all_cubes; };
			void loadProgram(ProgramType type, std::string vertexShader, std::string fragmentShader);
			void useProgram(ProgramType type);
			void create_uniform_matrices(ProgramType type);
			void drawCube(ProgramType cubeType);
			void recalculate_matrices(FreeFlyCamera &camera, Cube cube);
			void initAllCubes();
			void drawCubes(FreeFlyCamera &camera);
	};
}


#endif // WORLD_IMAKER_SCENE_HPP