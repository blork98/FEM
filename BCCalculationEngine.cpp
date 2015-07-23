#include <BCCalculationEngine.h>

BCCalculationEngine::BCCalculationEngine(
	const std::shared_ptr<FiniteElement2D>& masterElement,
	const std::shared_ptr<Mapping>& map, 
	const std::shared_ptr<Quadrature>& quadInfo,
	const std::shared_ptr<Mesh2D>& mesh,
		const std::shared_ptr<Data2D>& data)
	:masterElement_(masterElement), map_(map), 
	quadInfo_(quadInfo), mesh_(mesh), data_(data),
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

void BCCalculationEngine::apply_natural_bc( LAMatrix* const K, LAVector* const F) const
{
	//TODO
};

double BCCalculationEngine::calculate_y( unsigned int finiteElement, unsigned int nodeI) const
{
	double value = 0.0;

	using std::vector;
	const vector<unsigned int>& nodesInElement = mesh_->get_nodes_in_element(finiteElement);

	//get integration points
	const vector<double>& weights = quadInfo_->get_weights();
	const vector<vector<double>>& integrationPoints = quadInfo_->get_points();

	double y = 0.0,jacobian_det = 0.0;

	//integPoint is evaluation point ( ie integration point) 
	std::pair<double,double> integPoint;

	//get location of nodes of the element and put in pairs
	for( unsigned int i = 0; i < nodeLocations.size(); ++i )
		nodeLocations[i] = mesh_->get_node_location(nodesInElement[i]);

	//set node locations in mapping
	map_->set_node_locations(nodeLocations);

	const std::pair<double,double>& nodeLocation = mesh_->get_node_location(nodeI); 
	unsigned int nodeInMaster = mesh_->get_node_map_to_master(finiteElement,nodeI);

	for( unsigned int pointCtr = 0; pointCtr < weights.size(); ++pointCtr )
	{
		integPoint = std::make_pair(integrationPoints[pointCtr][0],integrationPoints[pointCtr][1]);


	};

	return value;
};