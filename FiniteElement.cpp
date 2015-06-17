#include "FiniteElement.h"

using std::vector;
using std::pair;


FiniteElement2D::FiniteElement2D(const unsigned int& numNodes,
		const vector<pair<double,double>>& nodeLocations,
		const vector<unsigned int>& nodeEnumerations)
	: numNodes_(numNodes), nodeLocations_(nodeLocations), 
	nodeEnumerations_(nodeEnumerations)
{};

FiniteElement2D::~FiniteElement2D(void)
{};

unsigned int FiniteElement2D::num_nodes() const
{
	return numNodes_;
};

const vector<unsigned int>& FiniteElement2D::node_enums() const
{
	return nodeEnumerations_;	
};

const vector<pair<double,double>>& FiniteElement2D::node_locations() const {
	return nodeLocations_;
}


