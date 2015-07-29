#include <FECalculationEngine.h>

FECalculationEngine2D::FECalculationEngine2D(
		const std::shared_ptr<FiniteElement2D>& masterElement,
		const std::shared_ptr<Mapping>& map, 
		const std::shared_ptr<Quadrature>& quadInfo,
		const std::shared_ptr<Mesh2D>& mesh,
		const std::shared_ptr<Data2D>& data )
		: masterElement_(masterElement), map_(map), quadInfo_(quadInfo),
		mesh_(mesh), data_(data), 
		jMatrix(quadInfo->num_dims()*quadInfo_->num_dims(),0.0),
		nodeLocations( masterElement->num_nodes(), std::make_pair(0.0,0.0)),
		masterToRealPoint(quadInfo->num_dims(),0.0)
{
	initialize();
};

void FECalculationEngine2D::initialize()
{
	map_->set_node_locations_master(masterElement_->node_locations());
};

void FECalculationEngine2D::set_master_element(const std::shared_ptr<FiniteElement2D>& masterElement)
{
	masterElement_= masterElement;
};

void FECalculationEngine2D::set_mapping(const std::shared_ptr<Mapping>& map)
{
	map_ = map;
};

void FECalculationEngine2D::set_quadrature(const std::shared_ptr<Quadrature>& quadInfo)
{
	quadInfo_ = quadInfo;
};

void FECalculationEngine2D::set_mesh(const std::shared_ptr<Mesh2D>& mesh)
{
	mesh_ = mesh;
};

const std::shared_ptr<FiniteElement2D>& FECalculationEngine2D::get_master_elem() const
{
	return masterElement_;
};

const std::shared_ptr<Mapping>& FECalculationEngine2D::get_mapping() const
{
	return map_;
};

const std::shared_ptr<Quadrature>& FECalculationEngine2D::get_quad_info() const
{
	return quadInfo_;	
};

const  std::shared_ptr<Mesh2D>& FECalculationEngine2D::get_mesh() const
{
	return mesh_;
};

double FECalculationEngine2D::calculate_f( unsigned int finiteElement, unsigned int node) const
{
	double value = 0.0;

	using std::vector;

	const vector<unsigned int>& nodesInElement = mesh_->get_nodes_in_element(finiteElement);

	//get integration points
	const vector<double>& weights = quadInfo_->get_weights();
	const vector<vector<double>>& integrationPoints = quadInfo_->get_points();

	double u = 0.0,f = 0.0,jacobian_det = 0.0;

	//integPoint is evaluation point ( ie integration point) 
	std::pair<double,double> integPoint;
	
	//get location of nodes of the element and put in pairs
	for( unsigned int i = 0; i < nodeLocations.size(); ++i )
		nodeLocations[i] = mesh_->get_node_location(nodesInElement[i]);

	//set node locations in mapping
	map_->set_node_locations(nodeLocations);

	const std::pair<double,double>& nodeLocation = mesh_->get_node_location(node); 
	unsigned int nodeInMaster = mesh_->get_node_map_to_master(finiteElement,node);

	for( unsigned int pointCtr = 0; pointCtr < weights.size(); ++pointCtr )
	{
		integPoint = std::make_pair(integrationPoints[pointCtr][0],integrationPoints[pointCtr][1]);

		map_->set_point(integrationPoints[pointCtr]);
		map_->transform_master_to_real(integrationPoints[pointCtr],masterToRealPoint);
		map_->get_jacobian_matrix(jMatrix,jacobian_det);

		u = masterElement_->shape_value(nodeInMaster,integPoint);
		f = data_->f_val(std::make_pair(masterToRealPoint[0],masterToRealPoint[1])); 
		value += u*f*jacobian_det*weights[pointCtr];

	};

	return value;
};

void FECalculationEngine2D::calculate_f( unsigned int finiteElement, LAVector& globalF) const
{
	using std::vector;

	const vector<unsigned int>& nodesInElement = mesh_->get_nodes_in_element(finiteElement);

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
		unsigned int nodeInMaster = mesh_->get_node_map_to_master(finiteElement,node);
		u = 0.0; 
		f = 0.0;
	
		//integration TODO: add weights
		for( unsigned int pointCtr = 0; pointCtr < weights.size(); ++pointCtr )
		{
			integPoint = std::make_pair(integrationPoints[pointCtr][0],integrationPoints[pointCtr][1]);

			map_->set_point(integrationPoints[pointCtr]);
			map_->transform_master_to_real(integrationPoints[pointCtr],masterToRealPoint);
			map_->get_jacobian_matrix(jMatrix,jacobian_det);

			u = masterElement_->shape_value(nodeInMaster,integPoint);
			f = data_->f_val(std::make_pair(masterToRealPoint[0],masterToRealPoint[1])); 
			globalF(node) += u*f*jacobian_det*weights[pointCtr];

		};
	};
};
//TODO:: change from vector<vector> to different type
void FECalculationEngine2D::calculate_k( unsigned int finiteElement, LAMatrix& matrix) const
{
	using std::vector;
	using std::pair;

	const vector<unsigned int>& nodesInElement = mesh_->get_nodes_in_element(finiteElement);

	//get integration points
	const vector<double>& weights = quadInfo_->get_weights();
	const vector<vector<double>>& integrationPoints = quadInfo_->get_points();

	//integPoint is evaluation point ( ie integration point) 
	std::pair<double,double> integPoint;
	
	//get location of nodes of the element and put in pairs
	for( unsigned int i = 0; i < nodeLocations.size(); ++i )
		nodeLocations[i] = mesh_->get_node_location(nodesInElement[i]);

	//set node locations in mapping
	map_->set_node_locations(nodeLocations);


	//variables
	double uI = 0.0, uJ = 0.0; 
	pair<double,double> dudenI, dudenJ;
	double k = 0.0, b = 0.0, jacobian_det = 0.0;
	double dudxI(0.0), dudyI(0.0), dudxJ(0.0), dudyJ(0.0);
	double kIJ(0.0);

	for( auto nodeI : nodesInElement ) 
	{
		for( auto nodeJ: nodesInElement )
		{
			const pair<double,double>& nodeLocationI = mesh_->get_node_location(nodeI); 
			const pair<double,double>& nodeLocationJ = mesh_->get_node_location(nodeJ); 

			unsigned int nodeInMasterI = mesh_->get_node_map_to_master(finiteElement,nodeI);
			unsigned int nodeInMasterJ = mesh_->get_node_map_to_master(finiteElement,nodeJ);

			kIJ = 0.0;

			for( unsigned int pointCtr = 0; pointCtr < weights.size(); ++pointCtr )
			{
				integPoint = std::make_pair(integrationPoints[pointCtr][0],integrationPoints[pointCtr][1]);

				map_->set_point(integrationPoints[pointCtr]);
				map_->transform_master_to_real(integrationPoints[pointCtr],masterToRealPoint);
				map_->get_jacobian_matrix(jMatrix,jacobian_det);

				k = data_->k_val(std::make_pair(masterToRealPoint[0],masterToRealPoint[1]));
				b = data_->b_val(std::make_pair(masterToRealPoint[0],masterToRealPoint[1]));

				uI = masterElement_->shape_value(nodeInMasterI,integPoint);
				uJ = masterElement_->shape_value(nodeInMasterJ,integPoint);
				dudenI = masterElement_->shape_values_grad(nodeInMasterI,integPoint);
				dudenJ = masterElement_->shape_values_grad(nodeInMasterJ,integPoint);

				dudxI = (1/jacobian_det)*(dudenI.first*jMatrix[0] + dudenI.second*jMatrix[2]);
				dudyI = (1/jacobian_det)*(dudenI.first*jMatrix[1] + dudenI.second*jMatrix[3]);

				dudxJ = (1/jacobian_det)*(dudenJ.first*jMatrix[0] + dudenJ.second*jMatrix[2]);
				dudyJ = (1/jacobian_det)*(dudenJ.first*jMatrix[1] + dudenJ.second*jMatrix[3]);

				kIJ += (k*(dudxI*dudxJ + dudyI*dudyJ) + b*uI*uJ)*weights[pointCtr];
			};

			matrix(nodeI,nodeJ) += kIJ; 

		};
	};
};

double FECalculationEngine2D::calculate_k( unsigned int finiteElement, unsigned int nodeI, unsigned int nodeJ ) const
{
	using std::vector;
	using std::pair;

	const vector<unsigned int>& nodesInElement = mesh_->get_nodes_in_element(finiteElement);

	//get integration points
	const vector<double>& weights = quadInfo_->get_weights();
	const vector<vector<double>>& integrationPoints = quadInfo_->get_points();

	//integPoint is evaluation point ( ie integration point) 
	std::pair<double,double> integPoint;
	
	//get location of nodes of the element and put in pairs
	for( unsigned int i = 0; i < nodeLocations.size(); ++i )
		nodeLocations[i] = mesh_->get_node_location(nodesInElement[i]);

	//set node locations in mapping
	map_->set_node_locations(nodeLocations);


	//variables
	double uI = 0.0, uJ = 0.0; 
	pair<double,double> dudenI, dudenJ;
	double k = 0.0, b = 0.0, jacobian_det = 0.0;
	double dudxI(0.0), dudyI(0.0), dudxJ(0.0), dudyJ(0.0);
	double kIJ(0.0);

	const pair<double,double>& nodeLocationI = mesh_->get_node_location(nodeI); 
	const pair<double,double>& nodeLocationJ = mesh_->get_node_location(nodeJ); 

	unsigned int nodeInMasterI = mesh_->get_node_map_to_master(finiteElement,nodeI);
	unsigned int nodeInMasterJ = mesh_->get_node_map_to_master(finiteElement,nodeJ);

	for( unsigned int pointCtr = 0; pointCtr < weights.size(); ++pointCtr )
	{
		integPoint = std::make_pair(integrationPoints[pointCtr][0],integrationPoints[pointCtr][1]);

		map_->set_point(integrationPoints[pointCtr]);
		map_->transform_master_to_real(integrationPoints[pointCtr],masterToRealPoint);
		map_->get_jacobian_matrix(jMatrix,jacobian_det);

		k = data_->k_val(std::make_pair(masterToRealPoint[0],masterToRealPoint[1]));
		b = data_->b_val(std::make_pair(masterToRealPoint[0],masterToRealPoint[1]));

		uI = masterElement_->shape_value(nodeInMasterI,integPoint);
		uJ = masterElement_->shape_value(nodeInMasterJ,integPoint);
		dudenI = masterElement_->shape_values_grad(nodeInMasterI,integPoint);
		dudenJ = masterElement_->shape_values_grad(nodeInMasterJ,integPoint);

		dudxI = (1/jacobian_det)*(dudenI.first*jMatrix[0] + dudenI.second*jMatrix[2]);
		dudyI = (1/jacobian_det)*(dudenI.first*jMatrix[1] + dudenI.second*jMatrix[3]);

		dudxJ = (1/jacobian_det)*(dudenJ.first*jMatrix[0] + dudenJ.second*jMatrix[2]);
		dudyJ = (1/jacobian_det)*(dudenJ.first*jMatrix[1] + dudenJ.second*jMatrix[3]);

		kIJ += (k*(dudxI*dudxJ + dudyI*dudyJ) + b*uI*uJ)*weights[pointCtr];
	};

	return kIJ;
};


