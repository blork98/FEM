#ifndef BCCALCULATIONENGINE_H_
#define BCCALCULATIONENGINE_H_

#include <memory>

#include <Mapping.h>
#include <FiniteElement.h>
#include <Quadrature.h>
#include <Mesh.h>
#include <Data.h>
#include <LAContainers.h>
#include <BoundaryCondition.h>

class BCCalculationEngine
{
public:
	BCCalculationEngine(const std::shared_ptr<FiniteElement2D>& masterElement,
		const std::shared_ptr<Mapping>& map, 
		const std::shared_ptr<Quadrature>& quadInfo,
		const std::shared_ptr<Mesh2D>& mesh,
		const std::shared_ptr<PointValueBC>& pbc,
		const std::shared_ptr<NaturalBC>& nbc);

	void set_master_element(const std::shared_ptr<FiniteElement2D>& masterElement);
	void set_mapping(const std::shared_ptr<Mapping>& map);
	void set_quadrature(const std::shared_ptr<Quadrature>& quadInfo);
	void set_mesh(const std::shared_ptr<Mesh2D>& mesh);

	const std::shared_ptr<FiniteElement2D>& get_master_elem() const;
	const std::shared_ptr<Mapping>& get_mapping() const;
	const std::shared_ptr<Quadrature>& get_quad_info() const;
	const std::shared_ptr<Mesh2D>& get_mesh() const;

	void apply_natural_bc( LAMatrix& K, LAVector& F) const;
	void apply_essential_bc( LAMatrix& K, LAVector& F) const;

private:
	std::shared_ptr<FiniteElement2D> masterElement_;
	std::shared_ptr<Mapping> map_;
	std::shared_ptr<Quadrature> quadInfo_;
	std::shared_ptr<Mesh2D> mesh_;
	std::shared_ptr<PointValueBC> pbc_;
	std::shared_ptr<NaturalBC> nbc_;

	mutable std::vector<std::pair<double,double>> nodeLocations;
	mutable std::vector<double> intPoint, masterToRealPoint, jMatrix;

	double calculate_p( unsigned int finiteElement, unsigned int nodeI, 
		unsigned int nodeJ, const std::pair<unsigned int,double>& dimInfo ) const;
	double calculate_y( unsigned int finiteElement, unsigned int nodeI, 
		const std::pair<unsigned int,double>& dimInfo) const;
};

#endif