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

#endif