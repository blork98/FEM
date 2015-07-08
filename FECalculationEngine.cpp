#include <FECalculationEngine.h>

FECalculationEngine2D::FECalculationEngine2D(
		const boost::shared_ptr<FiniteElement2D>& masterElement,
		const boost::shared_ptr<Mapping>& map, 
		const boost::shared_ptr<Quadrature>& quadInfo,
		const boost::shared_ptr<Mesh2D>& mesh,
		const boost::shared_ptr<Data2D>& data )
		: masterElement_(masterElement), map_(map), quadInfo_(quadInfo),
		mesh_(mesh), data_(data), 
		jMatrix(quadInfo->num_dims()*quadInfo_->num_dims(),0.0),
		nodeLocations( masterElement->num_nodes(), std::make_pair(0.0,0.0))
{
	initialize();
};

void FECalculationEngine2D::initialize()
{
	map_->set_node_locations_master(masterElement_->node_locations());
};

void FECalculationEngine2D::set_master_element(const boost::shared_ptr<FiniteElement2D>& masterElement)
{
	masterElement_= masterElement;
};

void FECalculationEngine2D::set_mapping(const boost::shared_ptr<Mapping>& map)
{
	map_ = map;
};

void FECalculationEngine2D::set_quadrature(const boost::shared_ptr<Quadrature>& quadInfo)
{
	quadInfo_ = quadInfo;
};

void FECalculationEngine2D::set_mesh(const boost::shared_ptr<Mesh2D>& mesh)
{
	mesh_ = mesh;
};

const boost::shared_ptr<FiniteElement2D>& FECalculationEngine2D::get_master_elem() const
{
	return masterElement_;
};

const boost::shared_ptr<Mapping>& FECalculationEngine2D::get_mapping() const
{
	return map_;
};

const boost::shared_ptr<Quadrature>& FECalculationEngine2D::get_quad_info() const
{
	return quadInfo_;	
};

const  boost::shared_ptr<Mesh2D>& FECalculationEngine2D::get_mesh() const
{
	return mesh_;
};

void FECalculationEngine2D::calculate_f( unsigned int element, std::vector<double>& globalF) const
{
	using std::vector;

	const vector<unsigned int>& nodesInElement = mesh_->get_nodes_in_element(element);

	//get integration points
	const vector<double>& weights = quadInfo_->get_weights();
	const vector<vector<double>>& integrationPoints = quadInfo_->get_points();

	double u,f,jacobian_det;

	//integPoint is evaluation point ( ie integration point) 
	std::pair<double,double> integPoint;
	
	//get location of nodes of the element and put in pairs
	for( unsigned int i = 0; i < nodeLocations.size(); ++i )
		nodeLocations[i] = mesh_->get_node_location(nodesInElement[i]);

	//set node locations in mapping
	map_->set_node_locations(nodeLocations);

	//each node in element
	for( auto node : nodesInElement )
	{
		const std::pair<double,double>& nodeLocation = mesh_->get_node_location(node); 
		unsigned int nodeInMaster = mesh_->get_node_map_to_master(node);
		globalF[node] = 0.0;
		u = 0.0; 
	
		//integration TODO: add weights
		for( unsigned int pointCtr = 0; pointCtr < weights.size(); ++pointCtr )
		{
			integPoint = std::make_pair(integrationPoints[pointCtr][0],integrationPoints[pointCtr][1]);

			map_->set_point(integrationPoints[pointCtr]);
			map_->transform_master_to_real(integrationPoints[pointCtr],masterToRealPoint);
			map_->get_jacobian_matrix(jMatrix,jacobian_det);

			u = masterElement_->shape_value(nodeInMaster,integPoint);
			f = data_->f_val(std::make_pair(masterToRealPoint[0],masterToRealPoint[1])); 
			globalF[node] += u*f*jacobian_det*weights[pointCtr];

		};
	};
};
