#ifndef BOUNDARYCONDITION_H_
#define BOUNDARYCONDITION_H_

#include<vector>

class PointValueBC
{
public:
	PointValueBC( const std::vector<unsigned int>& nodes,
		const std::vector<double>& vals);

	const std::vector<std::pair<unsigned int,double>>& point_values() const;

	typedef std::vector<std::pair<unsigned int,double>>::const_iterator const_iterator;

	const_iterator begin() const;
	const_iterator end() const;

private:
	std::vector<std::pair<unsigned int,double>> data_;
};

class NaturalBC
{
public:
    NaturalBC( std::vector<std::pair<unsigned int, std::vector<unsigned int>>>& boundaryElements );
        
    typedef std::vector<std::pair<unsigned int, std::vector<unsigned int>>>::const_iterator elem_iterator;
	typedef std::vector<unsigned int>::const_iterator node_iterator;

    elem_iterator elem_begin() const;
    elem_iterator elem_end() const;
	node_iterator node_in_elem_begin( elem_iterator elem) const;
	node_iterator node_in_elem_end( elem_iterator elem) const;

	const std::vector<std::pair<unsigned int, std::vector<unsigned int>>>& boundary_elems() const;
	const std::vector<unsigned int>& boundary_nodes_in_elem( unsigned int elem ) const;
    
    virtual double p(double x, double y) const = 0;
    virtual double y(double x, double y) const = 0;
    
private:
    std::vector<std::pair<unsigned int, std::vector<unsigned int>>> boundaryElements_;
};

class ConstantNaturalBC : public NaturalBC
{
public:
	ConstantNaturalBC( double p, double y, 
		std::vector<std::pair<unsigned int, std::vector<unsigned int>>>& boundaryElements);

	virtual double p(double x, double y) const;
    virtual double y(double x, double y) const;
private:
	double p_,y_;
};

#endif