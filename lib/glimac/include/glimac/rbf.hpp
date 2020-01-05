#ifndef WORLD_IMAKER_RBF_HPP 
#define WORLD_IMAKER_RBF_HPP
#pragma once
#include <glm/glm.hpp>
#include <glimac/GameController.hpp>
#include <math.h>
#include <vector>
#include <list>
#include <algorithm>
#include <numeric>
#include <eigen3/Eigen/Dense>

namespace glimac {

    ///set type of radial basis function
    enum class FunctionType
    {
        Gaussian,         // f(r) = exp(-(epsilon * r)^2)
        ThinPlateSpline,  // f(r) = (r^2) * log(r)
        InverseQuadratic, // f(r) = (1 + (epsilon * r)^2)^(-1)
        BiharmonicSpline, // f(r) = r
        Multiquadric,     // f(r) = sqrt(1 + (epsilon * r^2))
    };
    
    //set class control point in order to stock better the control points of the txt file
    ///RBF control points
    class ControlPoint
    {
    public:
        glm::ivec3 m_position;
        float m_value;
    };

    ///compute norm for RBF function
    const double norm(const glm::vec3 vec1);
    ///set RBF for each FunctionType
    float getRBF(FunctionType type, const glm::ivec3 v1, const glm::ivec3 v2, const float epsilon);
    ///compute omega for RBF function
    const Eigen::VectorXf find_omega(std::vector <ControlPoint> &ctrlPts);
    ///apply RBF function
    //void applyRbf(std::list <Cube> &allCubes, std::vector <ControlPoint> &ctrlPts, FunctionType type, GameController &gameControl);    
}

#endif