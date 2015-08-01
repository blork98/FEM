#ifndef QUADRILATERALFE_H_
#define QUADRILATERALFE_H_

#include <FiniteElement.h>

class BilinearQuadFE : public FiniteElement2D
{
public:
	BilinearQuadFE(	const std::vector<std::pair<double,double>>& nodeLocations,
					const std::vector<unsigned int>& nodeEnumerations);
	virtual ~BilinearQuadFE(void);

	unsigned int const_dim( unsigned int node1, unsigned int node2 ) const;
	virtual double shape_value ( const unsigned int& node, 
		const std::pair<double,double>& point) const;
	virtual std::pair<double,double> shape_values_grad(const unsigned int& node, 
		const std::pair<double,double>& point) const;
private:

};

#endif