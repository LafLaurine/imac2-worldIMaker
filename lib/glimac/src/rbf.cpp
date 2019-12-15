#include <glimac/rbf.hpp>
#include <iostream>

namespace glimac{
    template <typename T>
    T getRBF(FunctionType type, const std::vector<T> v1, const std::vector<T> v2, const T epsilon){
        if(type == FunctionType::Gaussian) {
            T d = vectors_distance(v1, v2);
            return exp(-epsilon*d*d); 
        }
        else if(type == FunctionType::InverseQuadratic) {
        }
    }

};