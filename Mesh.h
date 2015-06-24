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

class Mesh2D
{
  public:
	  Mesh2D( const boost::shared_ptr<FiniteElement2D>& masterElement,
		  const std::vector<std::pair<double,double>>& nodeLocations,
		  const std::vector<std::list<unsigned int>>& nodeAdjacency,
		  const std::vector<std::list<unsigned int>>& nodesInElement);

  private:
	  void create_mesh_elements();

	  boost::shared_ptr<FiniteElement2D> masterElement_;
	  std::vector<MeshElement2D> meshElements_;
	  unsigned int numElements_;

	  std::vector<std::pair<double,double>> nodeLocations_;
	  std::vector<std::list<unsigned int>> nodeAdjacency_, nodesInElement_;
};

#endif