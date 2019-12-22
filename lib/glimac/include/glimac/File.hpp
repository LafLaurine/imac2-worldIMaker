#ifndef FILE_HPP 
#define FILE_HPP

#pragma once

#include <SDL2/SDL.h>
#include <iostream>
#include <vector>
#include <cstddef>
#include <glimac/glm.hpp>
#include <glimac/GameController.hpp> 

namespace glimac {

//	void readFileControl(std::string filename,std::vector<ControlPoint> &ctrlPts);
	void saveFile(std::string filename,std::vector<Cube> &allCubes);
	void loadFile(std::string filename,std::vector<Cube> &allCubes,GameController &gameController);
}

#endif