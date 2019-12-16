#include <glimac/rbf.hpp>
#include <iostream>

namespace glimac{
    template <typename T>
    T getRBF(FunctionType type, const std::vector<T> v1, const std::vector<T> v2, const T epsilon){
        if(type == FunctionType::Gaussian) {
            T d = vectors_distance(v1, v2);
            return exp(-epsilon*d*d); 
        }
        else if(type == FunctionType::ThinPlateSpline) {
        	T d = vectors_distance(v1, v2);
            return pow(vectors_distance, 2)*log(vectors_distance);
        }
        else if(type == FunctionType::InverseQuadratic) {
        	T d = vectors_distance(v1, v2);
        	return pow(1+pow((epsilon*vectors_distance),2),-1);
        }
        else if(type == FunctionType::BiharmonicSpline) {
        	return vectors_distance(v1, v2);
        }
        else if(type == FunctionType::Multiquadric) {
        	T d = vectors_distance(v1, v2);
        	return sqrt(1+(epsilon*pow(vectors_distance,2)));  //sqrt(1 + (epsiolon * r^2))
        }
    }

};