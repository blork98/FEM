#include "test.h"
#include "util.h"

#include <FEM.h>

#include <iostream>
#include <memory>

void test_mapping()
{
    //initialize map
    std::vector< std::pair<double,double> > nodeLocations(4);
    nodeLocations[0] = std::make_pair(-1.0,-1.0);
    nodeLocations[1] = std::make_pair(1.0,-1.0);
    nodeLocations[2] = std::make_pair(1.0,1.0);
    nodeLocations[3] = std::make_pair(-1.0,1.0);
    
    BilinearQuadMapping2D map(nodeLocations);
    
    std::vector<double> rPoint(2,0.0), mPoint(2,0.0);
    
    //test master to master map
    map.set_node_locations(nodeLocations);
    for( unsigned int i = 0; i < nodeLocations.size(); ++i)
    {
        mPoint[0] = nodeLocations[i].first;
        mPoint[1] = nodeLocations[i].second;
        map.transform_master_to_real(mPoint,rPoint);
        std::cout<<"x: "<<rPoint[0]<<"   y: "<<rPoint[1]<<std::endl;
    };
    
    //Test master to different node
    std::cout<<std::endl;
    std::vector< std::pair<double,double>> nodeLoc2(4);
    nodeLoc2[0] = std::make_pair(0.0,0.0);
    nodeLoc2[1] = std::make_pair(1.0,0.0);
    nodeLoc2[2] = std::make_pair(1.0,1.0);
    nodeLoc2[3] = std::make_pair(0.0,1.0);
    map.set_node_locations(nodeLoc2);
    for( unsigned int i = 0; i < nodeLoc2.size(); ++i)
    {
        mPoint[0] = nodeLocations[i].first;
        mPoint[1] = nodeLocations[i].second;
        map.transform_master_to_real(mPoint,rPoint);
        std::cout<<"x: "<<rPoint[0]<<"   y: "<<rPoint[1]<<std::endl;
    };
    
    //test jacobian
    std::vector<double> evalPoint(2,0.0);
    double jacobian = 0.0;
    std::vector<double> results(4,0.0);
    evalPoint[0] = 0.5;
    evalPoint[1] = 0.5;
    map.set_node_locations(nodeLocations);
    map.set_point(evalPoint);
    map.get_jacobian_matrix(results,jacobian);
    
    std::cout<<" Det J:"<<jacobian<<std::endl;
    for( unsigned int i = 0; i < results.size(); ++i)
        std::cout<<results[i]<<std::endl;
    
    std::cout<<"Done"<<std::endl;
};

void test2DFEM()
{
	//Create Master Element
	std::vector<unsigned int> nodeEnums(4,0);
	nodeEnums[0] = 0;
	nodeEnums[1] = 1;
	nodeEnums[2] = 2;
	nodeEnums[3] = 3;
	std::vector<std::pair<double,double>> nodeLocations(4);
	nodeLocations[0] = std::make_pair(-1.0,-1.0);
	nodeLocations[1] = std::make_pair(1.0,-1.0);
	nodeLocations[2] = std::make_pair(1.0,1.0);
	nodeLocations[3] = std::make_pair(-1.0,1.0);
	std::shared_ptr<FiniteElement2D> masterElement =  create_finite_element(nodeEnums,nodeLocations);

	//Create Mesh
	std::shared_ptr<Mesh2D> mesh =  create_mesh_test(masterElement);

	/*
	//Test Node Locations
	unsigned int nodeMap;
	for ( unsigned int i = 0; i < mesh->num_elements(); ++i )
	{
		const std::vector<unsigned int>& nodesInElem = mesh->get_nodes_in_element(i);
		std::cout<<"Element:"<<i<<std::endl;
		for( unsigned int j  = 0; j < nodesInElem.size(); ++j )
		{
			nodeMap = mesh->get_node_map_to_master(i,nodesInElem[j]);
			std::cout<<"Global Node: "<< nodesInElem[j] << " Master Node:"<< nodeMap <<std::endl;
		};
	};
	*/

	//Create Quadrature
	size_t numDims = 2;
	size_t pointsPerDim = 3;
	std::shared_ptr<Quadrature> quadInfo = create_quadrature(numDims,pointsPerDim);

	//Create Map
	std::shared_ptr<Mapping> mapping = create_biliniear_mapping(nodeLocations);

	//Create Constant Data
	std::shared_ptr<Data2D> data = std::make_shared<ConstantData2D>(1,1,1,1,1);

	//Create Calculation Engine
	FECalculationEngine2D engine(masterElement,mapping,quadInfo,mesh,data);

	//Test F Calculations
	unsigned int numNodes = 9;
	std::cout<<"F Values"<<std::endl;
	std::vector<double> fValues(numNodes,0.0);
	for( unsigned int elemCtr = 0; elemCtr < mesh->num_elements(); ++elemCtr )
	{
		std::cout<<"Element:"<<elemCtr<<std::endl;
		engine.calculate_f(elemCtr,fValues);
		for( unsigned int i = 0; i <fValues.size(); ++i )
			std::cout<<"Node:"<<i<<" Value:"<<fValues[i]<<std::endl;
	};

};

void test_FEM()
{
	//////////////////////////////////////////////////////////////////////
	//Test Quadrature Generator
	QuadratureGenerator quadGen;
	const std::vector<double>& weights = quadGen.get_weights(3);
	const std::vector<double>& points = quadGen.get_points(3);

	//////////////////////////////////////////////////////////////////////
	// Test Quadrature
	size_t numDims = 2;
	size_t pointsPerDim = 3;
	Quadrature quadrature(numDims,pointsPerDim,quadGen);

	const std::vector<double>& weights2 = quadrature.get_weights();
	const std::vector<std::vector<double>>& points2 = quadrature.get_points();
	
	///////////////////////////////////////////////////////////////////////
	//Test Quadrilateral Finite Element
	std::vector<unsigned int> nodeEnums(4,0);
	nodeEnums[0] = 1;
	nodeEnums[1] = 2;
	nodeEnums[2] = 3;
	nodeEnums[3] = 4;

	std::vector<std::pair<double,double>> nodeLocations(4);
	nodeLocations[0] = std::make_pair(-1.0,-1.0);
	nodeLocations[1] = std::make_pair(1.0,-1.0);
	nodeLocations[2] = std::make_pair(1.0,1.0);
	nodeLocations[3] = std::make_pair(-1.0,1.0);

	BilinearQuadFE me(nodeLocations,nodeEnums);
	
	//Test Shape Function
	std::pair<double,double> point1;
	double shapeVal; 
	
	//test shape functions
	for( unsigned int shapeFunc = 1; shapeFunc <= me.num_nodes(); ++shapeFunc ) {
		for( unsigned int i = 0; i < me.num_nodes(); ++i ) {
			point1 = nodeLocations[i];
			shapeVal = me.shape_value(shapeFunc,point1);
			std::cout<<shapeVal<<" ";
		}
		std::cout<<std::endl;
	}

};
