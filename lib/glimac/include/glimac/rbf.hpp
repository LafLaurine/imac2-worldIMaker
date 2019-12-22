#ifndef WORLD_IMAKER_RBF_HPP 
#define WORLD_IMAKER_RBF_HPP
#pragma once
#include <glm/glm.hpp>
#include <glimac/Cube.hpp>
#include <math.h>
#include <vector>
#include <algorithm>
#include <numeric>
#include <eigen3/Eigen/Dense>

namespace glimac {
    enum class FunctionType
    {
        Gaussian,         // f(r) = exp(-(epsilon * r)^2)
        ThinPlateSpline,  // f(r) = (r^2) * log(r)
        InverseQuadratic, // f(r) = (1 + (epsilon * r)^2)^(-1)
        BiharmonicSpline, // f(r) = r
        Multiquadric,     // f(r) = sqrt(1 + (epsilon * r^2))
    };
    

    class ControlPoint
    {
    public:
        glm::vec3 m_position;
        float m_value;
        float m_weight;
    };

    const double phi(const double &d);
    const double norm(const glm::vec3 vec1);
    float getRBF(FunctionType type, const glm::vec3 v1, const glm::vec3 v2, const float epsilon);
    const Eigen::VectorXf find_omega(std::vector <ControlPoint> &ctrlPts);
    void applyRbf(std::vector <Cube> &allCubes,  std::vector <ControlPoint> &ctrlPts, FunctionType type);    
}

#endif