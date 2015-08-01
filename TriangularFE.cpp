#include <TriangulerFE.h>

BilinearTriFE::BilinearTriFE(
	const std::vector<std::pair<double,double>>& nodeLocations,
	const std::vector<unsigned int>& nodeEnumerations)
	:FiniteElement2D(3,nodeLocations,nodeEnumerations)
{};

unsigned int BilinearTriFE::const_dim( unsigned int node1, unsigned int node2 ) const
{
	//TODO;
	return 0;
};

double BilinearTriFE::shape_value ( const unsigned int& node, 
	const std::pair<double,double>& point) const
{
	double value = 0.0;
	unsigned int nodeLoc = convert_node_glob_to_loc(node);

	switch(nodeLoc) 
	{
		case 0:
			value = 1 - point.first - point.second;
			break;
		case 1:
			value = point.first;
			break;
		case 2:
			value = point.second;
			break;
		default:
			break;
	}

	return value;
};

std::pair<double,double> BilinearTriFE::shape_values_grad(
	const unsigned int& node, const std::pair<double,double>& point) const
{
	std::pair<double,double> value = std::make_pair(0.0,0.0);
	unsigned int nodeLoc = convert_node_glob_to_loc(node);

	switch(nodeLoc) 
	{
		case 0:
			value.first = -1.0;
			value.second = -1.0;
			break;
		case 1:
			value.first = 1.0;
			value.second = 0.0;
			break;
		case 2:
			value.first = 0.0;
			value.second = 1.0;
			break;
		default:
			break;
	}

	return value;
};