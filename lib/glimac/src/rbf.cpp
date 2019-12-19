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
/*
    float distance(Eigen::Vector2f p1, Eigen::Vector2f p2) {
        return sqrt(pow((p1.x - p2.x), 2) + pow((p1.y - p2.y), 2));
    }*/

    /*Eigen::VectorXd computeOmega(Eigen::Matrix3f X, Eigen::VectorXd u) {
        Eigen::ColPivHouseholderQR<Eigen::Matrix3f> dec(X);
        return dec.solve(u);
    }*/

    /*Eigen::VectorXd phi(Eigen::Matrix3f X, Eigen::VectorXd u) {
	    Eigen::VectorXd wk = computeOmega(X, u);
    }*/


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