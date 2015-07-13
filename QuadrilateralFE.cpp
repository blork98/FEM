#include <QuadrilateralFE.h>

using std::pair;
using std::vector;

BilinearQuadFE::BilinearQuadFE(	const vector<pair<double,double>>& nodeLocations,
								const vector<unsigned int>& nodeEnumerations)
	:FiniteElement2D(4,nodeLocations,nodeEnumerations)
{};

//TODO calculate normalizer
double BilinearQuadFE::shape_value ( const unsigned int& node, 
		const pair<double,double>& point) const
{
	unsigned int nodeLoc = convert_node_glob_to_loc(node);
	double value = 0.0, normalizer = 0.0;
	double x0 = 0.0, y0 = 0.0;

	switch(nodeLoc) {
		case 0:
			x0 = nodeLocations_[1].first;
			y0 = nodeLocations_[3].second;
			normalizer = 1/((x0 - nodeLocations_[0].first)*(y0 - nodeLocations_[0].second ));
			value = normalizer*(x0 - point.first)*(y0 - point.second);
			break;
		case 1:
			x0 = nodeLocations_[0].first;
			y0 = nodeLocations_[2].second;
			normalizer = 1/((x0 - nodeLocations_[1].first)*(y0 - nodeLocations_[1].second ));
			value = normalizer*(x0 - point.first)*(y0 - point.second);
			break;
		case 2:
			x0 = nodeLocations_[3].first;
			y0 = nodeLocations_[1].second;
			normalizer = 1/((x0 - nodeLocations_[2].first)*(y0 - nodeLocations_[2].second ));
			value = normalizer*(x0 - point.first)*(y0 - point.second);
			break;
		case 3:
			x0 = nodeLocations_[2].first;
			y0 = nodeLocations_[0].second;
			normalizer = 1/((x0 - nodeLocations_[3].first)*(y0 - nodeLocations_[3].second ));
			value = normalizer*(x0 - point.first)*(y0 - point.second);
			break;
		default:
			break;
	};

	return value;
};

std::pair<double,double> BilinearQuadFE::shape_values_grad(const unsigned int& node, 
		const pair<double,double>& point) const
{
	unsigned int nodeLoc = convert_node_glob_to_loc(node);
	std::pair<double,double> value = std::make_pair(0.0,0.0);
	double x0 = 0.0, y0 = 0.0, normalizer = 0.0;

	switch(nodeLoc) {
		case 0:
			x0 = nodeLocations_[1].first;
			y0 = nodeLocations_[3].second;
			normalizer = 1/((x0 - nodeLocations_[0].first)*(y0 - nodeLocations_[0].second ));
			//value = normalizer*(x0 - point.first)*(y0 - point.second);
			value.first = normalizer*(-1)*(y0 - point.second);
			value.second = normalizer*(x0 - point.first)*(-1);
			break;
		case 1:
			x0 = nodeLocations_[0].first;
			y0 = nodeLocations_[2].second;
			normalizer = 1/((x0 - nodeLocations_[1].first)*(y0 - nodeLocations_[1].second ));
			//value = normalizer*(x0 - point.first)*(y0 - point.second);
			value.first = normalizer*(-1)*(y0 - point.second);
			value.second = normalizer*(x0 - point.first)*(-1);
			break;
		case 2:
			x0 = nodeLocations_[3].first;
			y0 = nodeLocations_[1].second;
			normalizer = 1/((x0 - nodeLocations_[2].first)*(y0 - nodeLocations_[2].second ));
			//value = normalizer*(x0 - point.first)*(y0 - point.second);
			value.first = normalizer*(-1)*(y0 - point.second);
			value.second = normalizer*(x0 - point.first)*(-1);
			break;
		case 3:
			x0 = nodeLocations_[2].first;
			y0 = nodeLocations_[0].second;
			normalizer = 1/((x0 - nodeLocations_[3].first)*(y0 - nodeLocations_[3].second ));
			//value = normalizer*(x0 - point.first)*(y0 - point.second);
			value.first = normalizer*(-1)*(y0 - point.second);
			value.second = normalizer*(x0 - point.first)*(-1);
			break;
		default:
			break;
	};

	return value;
};