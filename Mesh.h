#ifndef MESH_H_
#define MESH_H_

#include <map>
#include <list>
#include <vector>

#include <memory>

class FiniteElement2D;
class Node2S;
class MeshElement2D;

//MAJOR CHANGES ON THIS ONE!!!
//change node+map_to_master
class Mesh2D
{
  public:
	  Mesh2D( const std::shared_ptr<FiniteElement2D>& masterElement,
		  const std::vector<std::pair<double,double>>& nodeLocations,
		  const std::vector<std::vector<unsigned int>>& nodeAdjacency,
		  const std::vector<std::vector<unsigned int>>& nodesInElement,
		  const std::vector<std::vector<unsigned int>>&nodeMapToMasterElem);

	  unsigned int numNodes() const;
	  unsigned int num_elements() const;
	  const std::vector<unsigned int>& get_nodes_in_element( unsigned int elem) const;
	  const std::pair<double,double>& get_node_location( unsigned int node ) const;
	  unsigned int get_node_map_to_master( unsigned int elem, unsigned int node) const;

  private:
	  void create_mesh_elements();

	  std::shared_ptr<FiniteElement2D> masterElement_;
	  unsigned int numElements_;

	  std::vector<std::vector<unsigned int>> nodeMapToMasterElem_;
	  std::vector<std::pair<double,double>> nodeLocations_;
	  std::vector<std::vector<unsigned int>> nodeAdjacency_, nodesInElement_;
};

#endif