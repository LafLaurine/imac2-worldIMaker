#ifndef WORLD_IMAKER_RBF_HPP 
#define WORLD_IMAKER_RBF_HPP
#pragma once
#include <glm/glm.hpp>
#include <math.h>
#include <vector>
#include <algorithm>
#include <numeric>

namespace glimac {
    enum class FunctionType
    {
        Gaussian,         // f(r) = exp(-(epsilon * r)^2)
        ThinPlateSpline,  // f(r) = (r^2) * log(r)
        InverseQuadratic, // f(r) = (1 + (epsilon * r)^2)^(-1)
        BiharmonicSpline, // f(r) = r
        Multiquadric,     // f(r) = sqrt(1 + (epsiolon * r^2))
    };

    template <typename T>
    double vectors_distance(const std::vector<T>& a, const std::vector<T>& b)
    {
        std::vector<double>	auxiliary;

        std::transform (a.begin(), a.end(), b.begin(), std::back_inserter(auxiliary),//
        [](T element1, T element2) {return pow((element1-element2),2);});
        auxiliary.shrink_to_fit();

        return  std::sqrt(std::accumulate(auxiliary.begin(), auxiliary.end(), 0.0));    
    } 

    template <typename T>
    // Data points
    /* std::vector<glm::vec3> get_control_points(const std::string &filename)*/
    // Function type
    T getRBF(FunctionType type, const std::vector<T> v1, const std::vector<T> v2, const T epsilon);
}

#endif