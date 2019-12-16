#include <glimac/Scene.hpp>
#include <iostream>

namespace glimac{

    void Scene::loadProgram(ProgramType type, std::string vertexShader, std::string fragmentShader) {
        m_programs.emplace(type, glimac::loadProgram(vertexShader,fragmentShader));
        //appel des cubes utilisant le type
	}

	void Scene::useProgram(ProgramType type) {
		m_programs[type].use();
	}

	void Scene::initAllCubes() {
        for(unsigned int i=0; i<m_length; i++)
		{
			for(unsigned int j=0; j<m_width; j++)
			{
				for (unsigned int layer=0; layer<3; layer++)
				{
					Cube new_cube = Cube(glm::vec3(i,layer,j), glm::vec3(0.2,1,0));
					m_all_cubes(i,j).push_back(new_cube);
					//std::cout << m_all_cubes(i,j).at(i).getPosition() << std::endl;
				}
			}
        } 
    }

    void Scene::renderAll(ProgramType type)
    {       
        for (unsigned int length=0; length<m_length; length++) 
        {
            for (unsigned int width=0; width<m_width; width++)
            {
                for(unsigned int i=0; i<3; i++)
                {
                    m_all_cubes(length,width).at(i).create_uniform_matrices(m_programs[type]);
                    m_all_cubes(length,width).at(i).draw();
                }
            }
        }
    }
}