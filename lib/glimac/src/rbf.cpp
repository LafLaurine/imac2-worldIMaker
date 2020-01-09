#include <glimac/rbf.hpp>
#include <assert.h>
#include <iostream>

namespace glimac{

  float getRBF(FunctionType type, const glm::vec3 v1, const glm::vec3 v2, const float epsilon){
    //get distance between two vectors
    float d = glm::distance(v1, v2);
    //set the function for different RBF 
    if(type == FunctionType::Gaussian) {
      return exp(-epsilon*d*d); 
    }
    else if(type == FunctionType::ThinPlateSpline) {
      return pow(d, 2.0f)*log(d);
    }
    else if(type == FunctionType::InverseQuadratic) {
      return pow(1.0f+pow((epsilon*d),2.0f),-1.0f);
    }
    else if(type == FunctionType::BiharmonicSpline) {
      if(d == 0) 
        return 1;
      else
        return -(epsilon)*d;
    }
    else if(type == FunctionType::Multiquadric) {
      return sqrt(1.0f+(epsilon*pow(d,2.0f)));
    }
    else return 0.f;
  }

  //compute norm
  const double norm(const glm::vec3 vec1){
    return( (double)sqrt(vec1.x*vec1.x + vec1.y*vec1.y + vec1.z*vec1.z ));
  } 

  const Eigen::VectorXf find_omega(std::vector <ControlPoint> &ctrlPts){
    Eigen::MatrixXf M_constraint = Eigen::MatrixXf::Zero(ctrlPts.size(), ctrlPts.size());
    Eigen::VectorXf weight = Eigen::VectorXf::Ones(ctrlPts.size());
    //fill the control point weight vector
    for(unsigned int h=0; h<ctrlPts.size(); h++){
        weight[h]=ctrlPts.at(h).m_value;
    }
    //fill our matrix
    for(unsigned int i=0; i<ctrlPts.size(); i++){
        for(unsigned int j=0; j<ctrlPts.size(); j++){
          M_constraint(i,j) = norm(ctrlPts.at(i).m_position-ctrlPts.at(j).m_position);
        }
    }
    //resolution of M_constraint*omega=weight
    //choice of QR method
    //This type of decomposition is often used for the calculation of solutions of non-square linear systems, 
    //in particular to determine the pseudo-inverse of a matrix
    Eigen::ColPivHouseholderQR<Eigen::MatrixXf> qr(M_constraint);
		Eigen::VectorXf omega = qr.solve(weight);
    return omega;
  }

  void applyRbf(std::list<Cube>& allCubes, std::vector<ControlPoint> &ctrlPts, FunctionType type, GameController &gamecontrol, Scene& scene){
    float epsilon = 0.8f;
    float value;
    Eigen::VectorXf omega = find_omega(ctrlPts);  
      for (int x = 0; x < scene.getWidth() ; x++) {
        for(int y = 0 ; y < scene.getHeight() ; y++) {
          for(int z = 0 ; z < scene.getLength() ; z++) {
            value=0;
            for (size_t i = 1; i < ctrlPts.size(); ++i){
              value+= getRBF(type, glm::vec3(float(x), float(y), float(z)), ctrlPts[i].m_position, epsilon)*(-omega[i]);
            }
            if (value >= 0.f )
              gamecontrol.addCube(Cube(glm::ivec3(x, y, z)));
          }
        }
      }
  }

};