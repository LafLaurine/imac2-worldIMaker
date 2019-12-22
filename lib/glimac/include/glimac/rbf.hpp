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

    template <typename T>
    T getRBF(FunctionType type, const std::vector<T> v1, const std::vector<T> v2, const T epsilon);
    // Data points
    std::vector<double> ys;
    std::vector<std::vector<double>> xs;
    std::vector<double> ws;
    const double norm(const glm::vec3 vec1);
    const double phi(const double &d);
    void generateCube(unsigned int nbControlPoints, Cube* cube, const std::vector<Cube*> controlPoints);
    // Function type
    
}

#endif