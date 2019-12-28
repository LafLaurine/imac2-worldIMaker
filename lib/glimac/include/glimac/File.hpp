#ifndef FILE_HPP 
#define FILE_HPP

#pragma once

#include <SDL2/SDL.h>
#include <iostream>
#include <vector>
#include <cstddef>
#include <glimac/glm.hpp>
#include <glimac/rbf.hpp>
#include <glimac/GameController.hpp> 

namespace glimac {
	///read file for RBF control points
	void readFileControl(std::string filename,std::vector<ControlPoint> &ctrlPts);
	///save game file
	void saveFile(std::string filePath, std::string filename,std::vector<Cube> &allCubes);
	///load game file
	void loadFile(std::string filePath, std::string filename,std::vector<Cube> &allCubes);
}

#endif