#ifndef MESH_H_
#define MESH_H_

#include <map>
#include <list>
#include <vector>

#include <boost/shared_ptr.hpp>

//Forward defined classes
class FiniteElement2D;
class Node2S;
class MeshElement2D;
//MAJOR CHANGES ON THIS ONE!!!
class Mesh2D
{
  public:
	  Mesh2D( const boost::shared_ptr<FiniteElement2D>& masterElement,
		  const std::vector<std::pair<double,double>>& nodeLocations,
		  const std::vector<std::vector<unsigned int>>& nodeAdjacency,
		  const std::vector<std::vector<unsigned int>>& nodesInElement,
		  const std::vector<unsigned int>&nodeMapToMasterElem);

	  unsigned int num_elements() const;
	  const std::vector<unsigned int>& get_nodes_in_element( unsigned int elem) const;
	  const std::pair<double,double>& get_node_location( unsigned int node ) const;
	  unsigned int get_node_map_to_master( unsigned int) const;

  private:
	  void create_mesh_elements();

	  boost::shared_ptr<FiniteElement2D> masterElement_;
	  std::vector<MeshElement2D> meshElements_;
	  unsigned int numElements_;

	  std::vector<unsigned int> nodeMapToMasterElem_;
	  std::vector<std::pair<double,double>> nodeLocations_;
	  std::vector<std::vector<unsigned int>> nodeAdjacency_, nodesInElement_;
};

#endif