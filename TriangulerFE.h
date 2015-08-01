#ifndef TRIANGULARFE_H_
#define TRIANGULARFE_H_

#include <FiniteElement.h>
//TODO: make shape and grad val more general
class BilinearTriFE : public FiniteElement2D
{
public:
	BilinearTriFE(	const std::vector<std::pair<double,double>>& nodeLocations,
					const std::vector<unsigned int>& nodeEnumerations);

	unsigned int const_dim( unsigned int node1, unsigned int node2 ) const;
	virtual double shape_value ( const unsigned int& node, 
		const std::pair<double,double>& point) const;
	virtual std::pair<double,double> shape_values_grad(const unsigned int& node, 
		const std::pair<double,double>& point) const;
};

#endif
