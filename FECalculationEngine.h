#ifndef FECALCULATIONENGINE_H_
#define FECALCULATIONENGINE_H_

#include <boost\shared_array.hpp>

#include <Mapping.h>
#include <FiniteElement.h>
#include <Quadrature.h>
#include <Mesh.h>
#include <Data.h>

class FECalculationEngine2D
{
public:
	FECalculationEngine2D(const boost::shared_ptr<FiniteElement2D>& masterElement,
		const boost::shared_ptr<Mapping>& map, 
		const boost::shared_ptr<Quadrature>& quadInfo,
		const boost::shared_ptr<Mesh2D>& mesh,
		const boost::shared_ptr<Data2D>& data );

	void set_master_element(const boost::shared_ptr<FiniteElement2D>& masterElement);
	void set_mapping(const boost::shared_ptr<Mapping>& map);
	void set_quadrature(const boost::shared_ptr<Quadrature>& quadInfo);
	void set_mesh(const boost::shared_ptr<Mesh2D>& mesh);

	const boost::shared_ptr<FiniteElement2D>& get_master_elem() const;
	const boost::shared_ptr<Mapping>& get_mapping() const;
	const boost::shared_ptr<Quadrature>& get_quad_info() const;
	const boost::shared_ptr<Mesh2D>& get_mesh() const;

	void calculate_f( unsigned int element, std::vector<double>& values) const;
	void calculate_k() const;

private:
	boost::shared_ptr<FiniteElement2D> masterElement_;
	boost::shared_ptr<Mapping> map_;
	boost::shared_ptr<Quadrature> quadInfo_;
	boost::shared_ptr<Mesh2D> mesh_;
	boost::shared_ptr<Data2D> data_;

	void initialize();

	mutable std::vector<double> masterToRealPoint, jMatrix;
	mutable std::vector<std::pair<double,double>> nodeLocations;
};

#endif