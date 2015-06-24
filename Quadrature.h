#ifndef QUADRATURE_H_
#define QUADRATURE_H_

#include <vector>
#include <boost/tuple/tuple.hpp>
#include <QuadratureGenerator.h>

class QuadratureGenerator;

class Quadrature
{
public:
	Quadrature( const size_t& numDims, const size_t& pointsPerDim, 
		const QuadratureGenerator& quadGen);

	size_t num_dims() const;
	size_t points_per_dim() const;
	size_t size() const;
	
	const std::vector<double>& get_weights() const;
	const double& get_weight(size_t i) const;
	const std::vector<std::vector<double>>& get_points() const;
	const std::vector<double>& get_point(size_t i) const;

protected:
	void initialize_quad_info(const QuadratureGenerator& quadGen);

	size_t numDims_;
	size_t pointsPerDim_;
	std::vector<double> weights_;
	std::vector<std::vector<double>> points_;
};

#endif