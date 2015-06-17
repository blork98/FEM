#include <QuadrilateralFE.h>

using std::pair;
using std::vector;

BilinearQuadFE::BilinearQuadFE(	const vector<pair<double,double>>& nodeLocations,
								const vector<unsigned int>& nodeEnumerations)
	:FiniteElement2D(4,nodeLocations,nodeEnumerations)
{};

double BilinearQuadFE::shape_value ( const unsigned int& node, 
		const pair<double,double>& point) const
{
	switch(node) {
		case 1:

			break;
		default:
			break;
	};
};


	virtual std::pair<double,double> shape_values_grad(const unsigned int& node, 
		const std::pair<double,double>& point) const = 0;