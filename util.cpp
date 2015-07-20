#include "util.h"

#include <iostream>

#include <boost/assign/list_of.hpp>

std::shared_ptr<FiniteElement2D> create_finite_element(
	const std::vector<unsigned int>& nodeEnums,
	const std::vector<std::pair<double,double>>& nodeLocations)
{
	return std::make_shared<BilinearQuadFE>(nodeLocations,nodeEnums);
};

std::shared_ptr<Mesh2D> create_mesh_test( 
	const std::shared_ptr<FiniteElement2D>& masterElement)
{
	//node locations
	std::vector<std::pair<double,double>> nodeLocations(9,std::make_pair(0.0,0.0));
	nodeLocations[0] = std::make_pair(-1.0,-1.0);
	nodeLocations[1] = std::make_pair(1.0,-1.0);
	nodeLocations[2] = std::make_pair(1.0,1.0);
	nodeLocations[3] = std::make_pair(-1.0,1.0);
	nodeLocations[4] = std::make_pair(3.0,-1.0);
	nodeLocations[5] = std::make_pair(3.0,1.0);
	nodeLocations[6] = std::make_pair(3.0,3.0);
	nodeLocations[7] = std::make_pair(1.0,3.0);
	nodeLocations[8] = std::make_pair(-1.0,3.0);

	//map to master element node
	std::vector<std::vector<unsigned int>> nodeMapToMasterElem(4);
	nodeMapToMasterElem[0] = boost::assign::list_of(0)(1)(2)(3);
	nodeMapToMasterElem[1] = boost::assign::list_of(1)(4)(5)(2);
	nodeMapToMasterElem[2] = boost::assign::list_of(2)(5)(6)(7);
	nodeMapToMasterElem[3] = boost::assign::list_of(3)(2)(7)(8);


	//node in element
	std::vector<std::vector<unsigned int>> nodesInElement(4);
	nodesInElement[0] = boost::assign::list_of(0)(1)(2)(3);
	nodesInElement[1] = boost::assign::list_of(1)(4)(5)(2);
	nodesInElement[2] = boost::assign::list_of(2)(5)(6)(7);
	nodesInElement[3] = boost::assign::list_of(3)(2)(7)(8);

	//node adjacency //todo
	std::vector<std::vector<unsigned int>> nodeAdjacency(9);
	nodeAdjacency[0] = boost::assign::list_of(3)(1);
	nodeAdjacency[1] = boost::assign::list_of(0)(2)(4);
	nodeAdjacency[2] = boost::assign::list_of(1)(3)(7)(5);
	nodeAdjacency[3] = boost::assign::list_of(0)(2)(8);
	nodeAdjacency[4] = boost::assign::list_of(1)(5);
	nodeAdjacency[5] = boost::assign::list_of(4)(2)(6);
	nodeAdjacency[6] = boost::assign::list_of(5)(7);
	nodeAdjacency[7] = boost::assign::list_of(6)(2)(8);
	nodeAdjacency[8] = boost::assign::list_of(7)(3);

	return std::make_shared<Mesh2D>(masterElement,nodeLocations,nodeAdjacency,nodesInElement,nodeMapToMasterElem);
};

std::shared_ptr<Quadrature> create_quadrature(
	unsigned int numDims, unsigned int pointsPerDim)
{
	QuadratureGenerator quadGen;
	return std::make_shared<Quadrature>(numDims,pointsPerDim,quadGen);
};

std::shared_ptr<Mapping> create_biliniear_mapping(
	const std::vector<std::pair<double,double>>& nodeLocations)
{
	return std::make_shared<BilinearQuadMapping2D>(nodeLocations);
};

void print_matrix( const std::vector<std::vector<double>>& matrix)
{
	unsigned int numRows = matrix.size();
	unsigned int numCols = matrix[0].size();

	for( unsigned int i = 0; i < numRows; ++i )
	{
		for( unsigned int j = 0; j < numCols; ++j )
		{
			std::cout<<matrix[i][j]<<",";
		}
		std::cout<<std::endl;
	};
};