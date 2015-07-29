#include <BoundaryCondition.h>

PointValueBC::PointValueBC( 
	const std::vector<unsigned int>& nodes,
	const std::vector<double>& vals)
	: data_(nodes.size())
{
	for( unsigned int i = 0; i < nodes.size(); ++i)
		data_[i] = std::make_pair(nodes[i],vals[i]);
};

const std::vector<std::pair<unsigned int,double>>& 
	PointValueBC::point_values() const
{
	return data_;
};

PointValueBC::const_iterator PointValueBC::begin() const
{
	return data_.begin();
};

PointValueBC::const_iterator PointValueBC::end() const
{
	return data_.end();
};

