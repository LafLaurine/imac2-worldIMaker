#include <iostream>
#include <fstream>
#include <algorithm>
#include <glimac/File.hpp>
#include <vector>
#include <glm/glm.hpp>

namespace glimac{
	/*

	void readFileControl(std::string filename,std::vector<ControlPoint> &ctrlPts){
	
		std::ifstream fichier("../assets/doc"+filename, std::ios::in); 

		if (fichier)
		{

    		std::string line;
   			
   			while(getline(fichier, line))
    		{
        		//if (line.size()>0)
   			//{
        			ControlPoint control;
        			fichier >> control.m_position.x;
        			fichier >> control.m_position.y;
        			fichier >> control.m_position.z;
        			fichier >> control.m_value;
        			
        			ctrlPts.push_back(control);

        		
    		//}
    	}

			fichier.close();  
		}
		 else  
                std::cerr << "Impossible d'ouvrir le fichier !" << std::endl; 

	}*/


    void saveFile(std::string filename,std::vector<Cube> &allCubes){
       
        std::ofstream fichier("../assets/doc/" + filename, std::ios::out | std::ios::trunc); 

        if(fichier)  
        {      

        for (long unsigned int i = 0; i < allCubes.size(); ++i)
         {
             fichier << allCubes[i].getPosition().x <<" ";
             fichier << allCubes[i].getPosition().y <<" ";
             fichier << allCubes[i].getPosition().z <<" ";
             fichier << allCubes[i].isVisible() << std::endl;
         }

            fichier.close();
			std::cout << "Your world is saved" << std::endl;  
        }
        else  
                std::cerr << "Cannot open file" << std::endl;
    }


}