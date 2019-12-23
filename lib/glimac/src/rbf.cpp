#include <glimac/rbf.hpp>
#include <assert.h>

namespace glimac{
    float getRBF(FunctionType type, const glm::vec3 v1, const glm::vec3 v2, const float epsilon){
        float d = glm::distance(v1, v2);
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
        	return d;
        }
        else if(type == FunctionType::Multiquadric) {
        	return sqrt(1.0f+(epsilon*pow(d,2.0f)));
        }
        else return 0.f;
    }

    //calcul de la norme
    const double norm(const glm::vec3 vec1){
        return( (double)sqrt(vec1.x*vec1.x + vec1.y*vec1.y + vec1.z*vec1.z ));
    } 


    const Eigen::VectorXf find_omega(std::vector <ControlPoint> &ctrlPts){
    Eigen::MatrixXf M_contrainte = Eigen::MatrixXf::Zero(ctrlPts.size(), ctrlPts.size());
    Eigen::VectorXf poids = Eigen::VectorXf::Ones(ctrlPts.size());

    //remplissage du vecteur de poids des points de controle
    for(unsigned int h=0; h<ctrlPts.size(); h++){
        poids[h]=ctrlPts[h].m_weight;
    }

    //remplissage de notre matrice 
    for(unsigned int i=0; i<ctrlPts.size(); i++){
        for(unsigned int j=0; j<ctrlPts.size(); j++){
            M_contrainte(i,j) = norm(ctrlPts[i].m_position-ctrlPts[j].m_position);
        }
    }
    
    //méthode de résolution de M_contrainte*omega=poids
    //On choisit la méthode LU car elle est plus rapide
    Eigen::PartialPivLU<Eigen::MatrixXf> lu(M_contrainte);
    Eigen::VectorXf omega = lu.solve(poids);

    return omega;
  }



  void applyRbf(std::vector <Cube> &allCubes, std::vector <ControlPoint> &ctrlPts, FunctionType type){
    float epsilon=1.f;
    float value;
    Eigen::VectorXf omega=find_omega(ctrlPts);

    for(Cube &c: allCubes){
      value=0;
      for (size_t i = 1; i < ctrlPts.size(); ++i){
        value+= getRBF(type, c.getPosition(), ctrlPts[i].m_position, epsilon)*omega[i];

      } 
      if (value >= 0.f )  c.setVisible();
      else c.setInvisible();
    }  
  }


};