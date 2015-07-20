#ifndef UTIL_H_
#define UTIL_H_

#include <FEM.h>
#include <memory>

std::shared_ptr<FiniteElement2D> create_finite_element(
	const std::vector<unsigned int>& nodeEnums,
	const std::vector<std::pair<double,double>>& nodeLocations);

std::shared_ptr<Mesh2D> create_mesh_test( 
	const std::shared_ptr<FiniteElement2D>& masterElement);

std::shared_ptr<Quadrature> create_quadrature(
	unsigned int numdins, unsigned int pointsPerDim);

std::shared_ptr<Mapping> create_biliniear_mapping(
	const std::vector<std::pair<double,double>>& nodeLocations);

void print_matrix( const std::vector<std::vector<double>>& matrix);


#endif