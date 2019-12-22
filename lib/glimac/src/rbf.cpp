#include <glimac/rbf.hpp>
#include <assert.h>

namespace glimac{
    template <typename T>
    T getRBF(FunctionType type, T d, const T epsilon){
        if(type == FunctionType::Gaussian) {
            return exp(-epsilon*d*d); 
        }
        else if(type == FunctionType::ThinPlateSpline) {
            return pow(d, 2)*log(d);
        }
        else if(type == FunctionType::InverseQuadratic) {
        	return pow(1+pow((epsilon*d),2),-1);
        }
        else if(type == FunctionType::BiharmonicSpline) {
        	return d;
        }
        else if(type == FunctionType::Multiquadric) {
        	return sqrt(1+(epsilon*pow(d,2)));
        }
    }

    const double norm(const glm::vec3 vec1){
        return( (double)sqrt(vec1.x*vec1.x + vec1.y*vec1.y + vec1.z*vec1.z ));
    } 


    const double phi(const double &d){
        return exp(-0.2*d*d);
    }


    void reset()
    {
        ys.clear();
        xs.clear();
        ws.clear();
    }

    void addCenterPoint(const double y, const std::vector<double>& x)
    {
        ys.push_back(y);
        xs.push_back(x);
    }

};