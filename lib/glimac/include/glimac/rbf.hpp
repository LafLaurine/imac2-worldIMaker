#ifndef WORLD_IMAKER_RBF_HPP 
#define WORLD_IMAKER_RBF_HPP
#pragma once

#include <Eigen/Dense>

namespace glimac {
    enum class FunctionType
    {
        Gaussian,         // f(r) = exp(-(epsilon * r)^2)
        ThinPlateSpline,  // f(r) = (r^2) * log(r)
        InverseQuadratic, // f(r) = (1 + (epsilon * r)^2)^(-1)
        BiharmonicSpline, // f(r) = r
        Multiquadric,     // f(r) = sqrt(1 + (epsiolon * r^2))
    };

    private:
    // Function type
    FunctionType functionType;
    //control parameter for some functions
    double epsilon;
    // Data points
    std::vector<double> ys;
    std::vector<std::vector<double>> xs;
    // Weights
    std::vector<double> w;

    // Returns f(r)
    double getRbfValue(const double r) const;
}