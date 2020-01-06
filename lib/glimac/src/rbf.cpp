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

  Eigen::VectorXf findOmega(std::vector <ControlPoint> &ctrlPts, FunctionType type,  const float epsilon){
    size_t size=ctrlPts.size();
    //Definition Matrix A
    Eigen::MatrixXf A=Eigen::MatrixXf::Zero(size,size);
    for (size_t i = 1; i < size; ++i){
      for (size_t j = 0; j < i; ++j){
        A(i,j)=getRBF(type, ctrlPts[i].m_position,ctrlPts[j].m_position, epsilon);
      }
    }
    
    Eigen::MatrixXf A_t=A.transpose();
    A=A+A_t;
    A=A+Eigen::MatrixXf::Identity(size,size)*getRBF(type, ctrlPts[0].m_position,ctrlPts[0].m_position, epsilon);

    //Definition Vector B
    Eigen::VectorXf B(size);
    for (size_t i=0; i<size; ++i){
      B[i]=ctrlPts[i].m_value;
    }

    //Definition Vector Solution
    Eigen::ColPivHouseholderQR<Eigen::MatrixXf> qr(A);
    Eigen::VectorXf vec_omega = qr.solve(B);
    return vec_omega;
  }

  void applyRbf(std::list<Cube>& allCubes, std::vector<ControlPoint> &ctrlPts, FunctionType type, GameController &gamecontrol, Scene& scene){
    float epsilon = 1.0f;
    float value;
    Eigen::VectorXf omega = findOmega(ctrlPts, type, epsilon);

      value=0;
      gamecontrol.cleanScene(allCubes);
      for (int x = 0; x < scene.getWidth() ; x++) {
        for(int y = 0 ; y < scene.getHeight() ; y++) {
          for(int z = 0 ; z < scene.getLength() ; z++) {

            for (size_t i = 1; i < ctrlPts.size(); ++i){
              value+= getRBF(type, glm::vec3(float(x), float(y), float(z)), ctrlPts[i].m_position, epsilon)*omega[i];
              std::cout << ctrlPts[i].m_position << std::endl;
            }

            if (value >= 0.f )
              gamecontrol.addCube(Cube(glm::ivec3(x, y, z)));  
            //else 
              //gamecontrol.deleteCube(&c);
          }
        }
      }
  }

};