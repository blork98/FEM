#ifndef FINITE_ELEMENT_H_
#define FINITE_ELEMENT_H_

#include <vector>
#include <utility>

//FE class implements shape functions, values and derivatives

class FiniteElement2D
{
public:
	FiniteElement2D(const unsigned int& numNodes,
				const std::vector<std::pair<double,double>>& nodeLocations,
				const std::vector<unsigned int>& nodeEnumerations);
	virtual ~FiniteElement2D(void);

	unsigned int num_nodes() const;
	const std::vector<unsigned int>& node_enums() const;
	const std::vector<std::pair<double,double>>& node_locations() const;

	//Shape Function Values
	virtual double shape_value ( const unsigned int& node, 
		const std::pair<double,double>& point) const = 0;
	virtual std::pair<double,double> shape_values_grad(const unsigned int& node, 
		const std::pair<double,double>& point) const = 0;

private:
	unsigned int numNodes_;
	std::vector<std::pair<double,double>> nodeLocations_;
	std::vector<unsigned int> nodeEnumerations_;
};

#endif

