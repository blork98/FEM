#include "FiniteElement.h"


FiniteElement::FiniteElement(const unsigned int& numNodes,
		const std::vector<std::pair<double,double>>& nodeLocations,
		const std::vector<unsigned int>& nodeEnumerations)
	: numNodes_(numNodes), nodeLocations_(nodeLocations), 
	nodeEnumerations_(nodeEnumerations)
{};

FiniteElement::~FiniteElement(void)
{};

unsigned int FiniteElement::get_num_nodes() const
{
	return numNodes_;
};


