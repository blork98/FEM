#ifndef FECALCULATIONENGINE_H_
#define FECALCULATIONENGINE_H_

#include <memory>

#include <Mapping.h>
#include <FiniteElement.h>
#include <Quadrature.h>
#include <Mesh.h>
#include <Data.h>

class FECalculationEngine2D
{
public:
	FECalculationEngine2D(const std::shared_ptr<FiniteElement2D>& masterElement,
		const std::shared_ptr<Mapping>& map, 
		const std::shared_ptr<Quadrature>& quadInfo,
		const std::shared_ptr<Mesh2D>& mesh,
		const std::shared_ptr<Data2D>& data );

	void set_master_element(const std::shared_ptr<FiniteElement2D>& masterElement);
	void set_mapping(const std::shared_ptr<Mapping>& map);
	void set_quadrature(const std::shared_ptr<Quadrature>& quadInfo);
	void set_mesh(const std::shared_ptr<Mesh2D>& mesh);

	const std::shared_ptr<FiniteElement2D>& get_master_elem() const;
	const std::shared_ptr<Mapping>& get_mapping() const;
	const std::shared_ptr<Quadrature>& get_quad_info() const;
	const std::shared_ptr<Mesh2D>& get_mesh() const;

	void calculate_f( unsigned int element, std::vector<double>& values) const;
	void calculate_k( unsigned int element) const;

private:
	std::shared_ptr<FiniteElement2D> masterElement_;
	std::shared_ptr<Mapping> map_;
	std::shared_ptr<Quadrature> quadInfo_;
	std::shared_ptr<Mesh2D> mesh_;
	std::shared_ptr<Data2D> data_;

	void initialize();

	mutable std::vector<double> masterToRealPoint, jMatrix;
	mutable std::vector<std::pair<double,double>> nodeLocations;
};

#endif