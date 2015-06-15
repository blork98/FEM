#ifndef FINITE_ELEMENT_H_
#define FINITE_ELEMENT_H_

#include <vector>
#include <utility>

//FE class implements shape functions, values and derivatives

class FiniteElement
{
public:
	FiniteElement(const unsigned int& numNodes,
				const std::vector<std::pair<double,double>>& nodeLocations,
				const std::vector<unsigned int>& nodeEnumerations);
	virtual ~FiniteElement(void);

	unsigned int get_num_nodes() const;

	virtual double shape_value ( const unsigned int& node, 
								const std::pair<double,double>& point) const;
	virtual std::pair<double,double> shape_values_grad(const unsigned int& node, 
													const std::pair<double,double>& point) const;

private:
	unsigned int numNodes_;
	std::vector<std::pair<double,double>> nodeLocations_;
	std::vector<unsigned int> nodeEnumerations_;
};

#endif

