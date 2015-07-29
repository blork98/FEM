#ifndef BOUNDARYCONDITION_H_
#define BOUNDARYCONDITION_H_

#include<vector>
#include<algorithm>

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
   
    elem_iterator elem_begin() const;
    elem_iterator elem_end() const;

	const std::vector<std::pair<unsigned int, std::vector<unsigned int>>>& boundary_elems() const;
    
    virtual double p(double x, double y) const = 0;
    virtual double y(double x, double y) const = 0;
    
private:
    std::vector<std::pair<unsigned int, std::vector<unsigned int>>> boundaryElements_;
};

#endif