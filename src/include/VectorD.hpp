#ifndef __VECTORD_HPP__
#define __VECTORD_HPP__

#include <iostream>
#include <fstream>
#include <algorithm>
#include <cmath>

//public permet à tous les éléments d'accéder aux attr
//private autorise seleulement les méthodes de la classe à utiliser ces attr

class VectorD
{
	public:
	//Constructeur par défaut
	VectorD();
	//Constructeurs
	VectorD(const size_t &size);
	//Constructeur copie
	VectorD(const VectorD &vec);
	//Destructeur
	~VectorD();
	//inline permet condenser code, en particulier pour les accesseurs d'une classe
	inline size_t size() const{return _size;}

	double& operator[](const size_t i);
	const double& operator[](const size_t i) const;
	/// \brief computes the dot product between two vectors
	/// \param v : vector used for the dot product with this
	/// \return the result (scalar) of the dot product between 2 vectors
	double dot(const VectorD &v) const;
	double norme() const;	
	void normalize();

	VectorD operator+(const VectorD &v2)const;
	VectorD operator=(const VectorD &v);
	/*void saveFile();
	void VecFromFile();*/

	int save(const std::string &filename) const;
	//pas besoin instance pour appeler static
	static VectorD load(const std::string &filename);
	
	protected:
	size_t _size;
	//données
	double *_data;
};

std::ostream &operator<<(std::ostream &stream, const VectorD &vec);

#endif // __VECTORD_HPP__
