#include <iostream>
#include <fstream>
#include <algorithm>
#include <glimac/File.hpp>
#include <vector>
#include <glm/glm.hpp>

namespace glimac{

	void readFileControl(std::string filename,std::vector<ControlPoint> &ctrlPts){
        //search the file 
		std::ifstream file("../assets/doc/"+filename, std::ios::in); 
        assert(file.is_open() && "Unable to open control points file");
		std::string line;
            //read each line	
   			while(getline(file, line))
    		{
                //affect each number to the corresponding attributes of the class ControlPoint
        		ControlPoint control;
        		file >> control.m_position.x;
        		file >> control.m_position.y;
        		file >> control.m_position.z;
                file >> control.m_value;
                //fill the vector with the control class that contains everything we need to know about control points
        		ctrlPts.push_back(control);
    	    }
            //after reading, close the file
			file.close();  
	}

    void saveFile(std::string filePath,std::string filename,std::list<Cube> &allCubes, Scene &scene){
        //create a file
        std::ofstream file(filePath + filename, std::ios::out | std::ios::trunc); 
        if(file)  
        {

            std::for_each(allCubes.begin(), allCubes.end(), [&file](Cube& cube){
                //each position of the cube is write into the file
                file << cube.getPosition().x <<" ";
                file << cube.getPosition().y <<" ";
                file << cube.getPosition().z << " ";
                file << cube.getColor().x << " ";
                file << cube.getColor().y << " ";
                file << cube.getColor().z << " ";
                file << cube.getColor().w << std::endl;
            });

                //after constructing the file, close it
                file.close();
                std::cout << "Your world is saved" << std::endl;  
        }
        else  {
            std::cout << filePath << std::endl;
            std::cout << filename << std::endl;
            std::cerr << "Cannot write file" << std::endl;
        }
    }

	 void loadFile(std::string filePath, std::string filename,std::list<Cube> &allCubes, Scene &scene){
        allCubes.clear();
        std::cout << "world loaded" << std::endl;
        //search file
        std::ifstream file(filePath + filename, std::ios::in);  

        // clean list and array of all cubes
        allCubes = std::list<Cube>();
        for (int z = 0; z < scene.getLength() ; z++) {
            for(int x= 0 ; x <scene.getWidth() ; x++) {
                for(int y= 1 ; y < scene.getHeight() ; y++) {
                    allCubes.remove(*scene.tabCubes[x][y][z]);
                    scene.tabCubes[x][y][z] = nullptr;

                }
            }
        }

        // put only what there was in the saved scene
        if (file)
        {
            std::string line;
            glm::ivec3 position;
            glm::vec4 color;
            //get position and visibility from the file
            file >> position.x;
            file >> position.y;
            file >> position.z;
            file >> color.x;
            //std::cout << "COLOR X : " << color.x << std::endl;
            file >> color.y;
            //std::cout << "COLOR Y : " << color.y << std::endl;
            file >> color.z;
            //std::cout << "COLOR Z : " << color.z << std::endl;
            file >> color.w;
            //std::cout << "COLOR W : " << color.w << std::endl;

            //set position received to the scene's first cube*/
            Cube cube(glm::ivec3( position.x, position.y, position.z), color);
            allCubes.push_front(cube);
            

            //do the scene for every others cubes
            while(getline(file, line))
            {
                glm::ivec3 position;
                
                file >> position.x ;
                file >> position.y ;
                file >> position.z ;
                file >> color.x;
                file >> color.y;
                file >> color.z;
                
                Cube cube(glm::ivec3( position.x, position.y, position.z),color);
                allCubes.push_back(cube);
                scene.tabCubes[cube.getPosition().x][cube.getPosition().y][cube.getPosition().z] = &allCubes.back();                
            }
            //when task finished, close the file
            file.close();  
        }
         else  
            std::cerr << "Cannot open file !" << std::endl; 

    }

}