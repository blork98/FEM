#include <BCCalculationEngine.h>

#include <boost/bind.hpp>
#include <functional>
#include <cmath>

BCCalculationEngine::BCCalculationEngine(
	const std::shared_ptr<FiniteElement2D>& masterElement,
	const std::shared_ptr<Mapping>& map, 
	const std::shared_ptr<Quadrature>& quadInfo,
	const std::shared_ptr<Mesh2D>& mesh,
	const std::shared_ptr<PointValueBC>& pbc,
	const std::shared_ptr<NaturalBC>& nbc)
	:masterElement_(masterElement), map_(map), 
	quadInfo_(quadInfo), mesh_(mesh), 
	pbc_(pbc), nbc_(nbc), 
	intPoint(map->dim(),0.0), masterToRealPoint(map->dim(),0.0),
	jMatrix(map->dim()*map->dim(),0.0),
	nodeLocations( masterElement->num_nodes(), std::make_pair(0.0,0.0))
{
	map_->set_node_locations_master(masterElement_->node_locations());
};

void BCCalculationEngine::set_master_element(const std::shared_ptr<FiniteElement2D>& masterElement)
{
	masterElement_= masterElement;
};

void BCCalculationEngine::set_mapping(const std::shared_ptr<Mapping>& map)
{
	map_ = map;
};

void BCCalculationEngine::set_quadrature(const std::shared_ptr<Quadrature>& quadInfo)
{
	quadInfo_ = quadInfo;
};

void BCCalculationEngine::set_mesh(const std::shared_ptr<Mesh2D>& mesh)
{
	mesh_ = mesh;
};

const std::shared_ptr<FiniteElement2D>& BCCalculationEngine::get_master_elem() const
{
	return masterElement_;
};

const std::shared_ptr<Mapping>& BCCalculationEngine::get_mapping() const
{
	return map_;
};

const std::shared_ptr<Quadrature>& BCCalculationEngine::get_quad_info() const
{
	return quadInfo_;	
};

const  std::shared_ptr<Mesh2D>& BCCalculationEngine::get_mesh() const
{
	return mesh_;
};

void BCCalculationEngine::apply_essential_bc( LAMatrix& K, LAVector& F) const
{
	auto pbcIt = pbc_->begin();
	unsigned int nodeLoc = 0;
	double val = 0.0;

	for(; pbcIt != pbc_->end(); ++pbcIt)
	{
		nodeLoc = pbcIt->first;
		val = pbcIt->second;
		F(nodeLoc) += val;
	};
};

void BCCalculationEngine::apply_natural_bc( LAMatrix& K, LAVector& F) const
{
	//For p calculations
	std::pair<unsigned int, double> dimInfo = std::make_pair(0,0.0);
	std::pair<double,double> nodeLocation = std::make_pair(0.0,0.0);

	for( auto elemCtr = nbc_->elem_begin(); elemCtr != nbc_->elem_end(); ++elemCtr )
	{	
		const std::vector<unsigned int>& boundaryNodes = elemCtr->second;
		nodeLocation = mesh_->get_node_location(boundaryNodes[0]);
		dimInfo.first = masterElement_->const_dim(boundaryNodes);
		dimInfo.second = dimInfo.first == 0 ? nodeLocation.first : nodeLocation.second;

		for( auto nodeI : boundaryNodes )
		{
			F(nodeI) += calculate_y(elemCtr->first,nodeI,dimInfo);
			for( auto nodeJ : boundaryNodes )
				K(nodeI,nodeJ) += calculate_p(elemCtr->first, nodeI, nodeJ, dimInfo);
		};
	};
};

double BCCalculationEngine::calculate_y( unsigned int finiteElement, 
	unsigned int nodeI, const std::pair<unsigned int,double>& dimInfo) const
{
	double value = 0.0;

	using std::vector;
	const vector<unsigned int>& nodesInElement = mesh_->get_nodes_in_element(finiteElement);

	//get integration points
	const vector<double>& weights = quadInfo_->get_weights();
	const vector<vector<double>>& integrationPoints = quadInfo_->get_points();

	double y = 0.0, jacobian_det = 0.0, u = 0.0;

	//integPoint is evaluation point ( ie integration point) 
	std::pair<double,double> integPoint;

	//get location of nodes of the element and put in pairs
	for( unsigned int i = 0; i < nodeLocations.size(); ++i )
		nodeLocations[i] = mesh_->get_node_location(nodesInElement[i]);

	//set node locations in mapping
	map_->set_node_locations(nodeLocations);

	const std::pair<double,double>& nodeLocation = mesh_->get_node_location(nodeI); 
	unsigned int nodeInMaster = mesh_->get_node_map_to_master(finiteElement,nodeI);

	double dy = 0.0; double dx = 0.0;

	for( unsigned int pointCtr = 0; pointCtr < weights.size(); ++pointCtr )
	{
		//constant e
		if( dimInfo.first == 0 ) {
			integPoint = std::make_pair(dimInfo.second,integrationPoints[pointCtr][1]);
			intPoint[0] = dimInfo.second;
			intPoint[1] = integrationPoints[pointCtr][1];

			map_->set_point(intPoint);
			map_->transform_master_to_real(intPoint,masterToRealPoint);
			map_->get_jacobian_matrix(jMatrix,jacobian_det);

			dx = jMatrix[3]*jacobian_det;
			dy = jMatrix[2]*jacobian_det*-1.0;
			jacobian_det = std::sqrt((dx*dx) + (dy*dy));
		} else { //constant n
			integPoint = std::make_pair(integrationPoints[pointCtr][0],dimInfo.second);
			intPoint[0] = integrationPoints[pointCtr][0];
			intPoint[1] = dimInfo.second;

			map_->set_point(intPoint);
			map_->transform_master_to_real(intPoint,masterToRealPoint);
			map_->get_jacobian_matrix(jMatrix,jacobian_det);

			dx = jMatrix[0]*jacobian_det;
			dy = jMatrix[1]*jacobian_det*-1.0;
			jacobian_det = std::sqrt((dx*dx) + (dy*dy));
		};

		y = nbc_->y(masterToRealPoint[0],masterToRealPoint[1]);
		u = masterElement_->shape_value(nodeInMaster,integPoint);
		value += jacobian_det*u*y*weights[pointCtr];
	};

	return value;
};

double BCCalculationEngine::calculate_p( unsigned int finiteElement, unsigned int nodeI, 
		unsigned int nodeJ, const std::pair<unsigned int,double>& dimInfo ) const
{
	double value = 0.0;

	using std::vector;
	const vector<unsigned int>& nodesInElement = mesh_->get_nodes_in_element(finiteElement);

	//get integration points
	const vector<double>& weights = quadInfo_->get_weights();
	const vector<vector<double>>& integrationPoints = quadInfo_->get_points();

	double jacobian_det = 0.0, uI = 0.0, uJ = 0.0,p = 0.0;

	//integPoint is evaluation point ( ie integration point) 
	std::pair<double,double> integPoint;

	//get location of nodes of the element and put in pairs
	for( unsigned int i = 0; i < nodeLocations.size(); ++i )
		nodeLocations[i] = mesh_->get_node_location(nodesInElement[i]);

	//set node locations in mapping
	map_->set_node_locations(nodeLocations);

	const std::pair<double,double>& nodeLocation = mesh_->get_node_location(nodeI); 
	unsigned int nodeInMasterI = mesh_->get_node_map_to_master(finiteElement,nodeI);
	unsigned int nodeInMasterJ = mesh_->get_node_map_to_master(finiteElement,nodeJ);

	double dy = 0.0; double dx = 0.0;

	for( unsigned int pointCtr = 0; pointCtr < weights.size(); ++pointCtr )
	{
		//constant e
		if( dimInfo.first == 0 ) {
			integPoint = std::make_pair(dimInfo.second,integrationPoints[pointCtr][1]);
			intPoint[0] = dimInfo.second;
			intPoint[1] = integrationPoints[pointCtr][1];

			map_->set_point(intPoint);
			map_->transform_master_to_real(intPoint,masterToRealPoint);
			map_->get_jacobian_matrix(jMatrix,jacobian_det);

			dx = jMatrix[3]*jacobian_det;
			dy = jMatrix[2]*jacobian_det*-1.0;
			jacobian_det = std::sqrt((dx*dx) + (dy*dy));
		} else { //constant n
			integPoint = std::make_pair(integrationPoints[pointCtr][0],dimInfo.second);
			intPoint[0] = integrationPoints[pointCtr][0];
			intPoint[1] = dimInfo.second;

			map_->set_point(intPoint);
			map_->transform_master_to_real(intPoint,masterToRealPoint);
			map_->get_jacobian_matrix(jMatrix,jacobian_det);

			dx = jMatrix[0]*jacobian_det;
			dy = jMatrix[1]*jacobian_det*-1.0;
			jacobian_det = std::sqrt((dx*dx) + (dy*dy));
		};

		p = nbc_->p(masterToRealPoint[0],masterToRealPoint[1]);
		uI = masterElement_->shape_value(nodeInMasterI,integPoint);
		uJ = masterElement_->shape_value(nodeInMasterJ,integPoint);
		value += jacobian_det*uI*uJ*p*weights[pointCtr];
	};

	return value;
};