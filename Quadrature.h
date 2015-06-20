#ifndef QUADRATURE_H_
#define QUADRATURE_H_

#include<vector>

//pass singleton class which generates quad points 1D and this class converts it to 2D, 3D etc
class QuadratureGenerator1D;

class Quadrature
{
public:
	Quadrature( const unsigned int& numDims, const unsigned int& pointsPerDim);

	unsigned int num_dims() const;
	unsigned int points_per_dim() const;

	const std::pair<std::vector<double>,double>& get_quad_info(const unsigned int& i) const;
	
protected:
	void initialize_quad_info();

	unsigned int numDims_;
	unsigned int pointsPerDim_;
	std::pair<std::vector<double>,double> quadInfo_;
};

#endif