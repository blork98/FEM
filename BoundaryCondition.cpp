#include <BoundaryCondition.h>

#include<algorithm>

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
	return data_.cbegin();
};

PointValueBC::const_iterator PointValueBC::end() const
{
	return data_.end();
};

NaturalBC::NaturalBC( 
	std::vector<std::pair<unsigned int, std::vector<unsigned int>>>& boundaryElements)
	: boundaryElements_(boundaryElements)
{};

const std::vector<std::pair<unsigned int, std::vector<unsigned int>>>& 
	NaturalBC::boundary_elems() const
{
	return boundaryElements_;
};

const std::vector<unsigned int>& 
	NaturalBC::boundary_nodes_in_elem( unsigned int elem ) const
{
	auto it = std::find_if( boundaryElements_.cbegin(), boundaryElements_.end(),
		[&elem](const std::pair<unsigned int, std::vector<unsigned int>>& comp)
			{
				return comp.first == elem;
			});

	return (*it).second;
};

NaturalBC::elem_iterator NaturalBC::elem_begin() const{
	return boundaryElements_.cbegin();
};

NaturalBC::elem_iterator NaturalBC::elem_end() const
{
	return boundaryElements_.end();
};

NaturalBC::node_iterator NaturalBC::node_in_elem_begin( NaturalBC::elem_iterator elem) const
{
	return (*elem).second.cbegin();
};

NaturalBC::node_iterator NaturalBC::node_in_elem_end( NaturalBC::elem_iterator elem) const
{
	return (*elem).second.end();
};

ConstantNaturalBC::ConstantNaturalBC( double p, double y, 
	std::vector<std::pair<unsigned int, std::vector<unsigned int>>>& boundaryElements)
	:NaturalBC(boundaryElements), p_(p), y_(y)
{};

double ConstantNaturalBC::p(double x, double y) const 
{
	return p_;
};

double ConstantNaturalBC::y(double x, double y) const
{
	return y_;
};


