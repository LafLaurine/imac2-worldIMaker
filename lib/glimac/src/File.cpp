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
		if(file)
		{
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
		 else  
            std::cerr << "Cannot open file!" << std::endl; 

	}

    void saveFile(std::string filePath,std::string filename,std::vector<Cube> &allCubes){
        //create a file
        std::ofstream file(filePath + filename, std::ios::out | std::ios::trunc); 
        if(file)  
        {
            //parse the scene      
            for (long unsigned int i = 0; i < allCubes.size(); ++i)
            {
                //each position of the cube is write into the file
                file << allCubes[i].getPosition().x <<" ";
                file << allCubes[i].getPosition().y <<" ";
                file << allCubes[i].getPosition().z <<" ";
                //write if the cube is visible or not (0 ou 1)
                file << allCubes[i].isVisible() << std::endl;
            }
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

	 void loadFile(std::string filePath, std::string filename,std::vector<Cube> &allCubes){
        //search file
        std::ifstream file(filePath + filename, std::ios::in); 

        if (file)
        {
            std::string line;
            int i=0;

            glm::vec3 position;
            bool visibility;
            //get position and visibility from the file
            file >> position.x ;
            file >> position.y ;
            file >> position.z ;
            file >> visibility;

            //set position received to the scene's first cube
            allCubes[0].setPosition(position);
            //if cube is visible, then set it visible or invisible if not
            if (visibility == true)
            {
              allCubes[0].setVisible();
            }
            else allCubes[0].setInvisible();

            //do the scene for every others cubes
            while(getline(file, line))
            {
                i++;  
                glm::vec3 position;
                
                file >> position.x ;
                file >> position.y ;
                file >> position.z ;
                file >> visibility;

                allCubes[i].setPosition(position);
                if (visibility == true)
                {
                allCubes[i].setVisible();
                }
                else allCubes[i].setInvisible();
                            
            }
            //when task finished, close the file
            file.close();  
        }
         else  
            std::cerr << "Cannot open file !" << std::endl; 

    }


}