#include <Mesh.h>

//////////////////////////////////////////////////////////////////////
// Node Class

class Node2D  //Note Need to change this
{
  public:
	Node2D( const unsigned int& nodeNum = 0 );
	
	unsigned int get_node_num() const;
	void set_node_num( const unsigned int& nodeNum );
	std::vector<std::pair<double,double>>::const_iterator
		get_location( const std::vector<std::pair<double,double>>& nodeLocations ) const;
	
  private:
	  unsigned int nodeNum_;

};

Node2D::Node2D( const unsigned int& nodeNum )
	:nodeNum_(nodeNum)
{};

unsigned int Node2D::get_node_num() const
{
	return nodeNum_;
};

void Node2D::set_node_num( const unsigned int& nodeNum )
{
	nodeNum_ = nodeNum;
};

std::vector<std::pair<double,double>>::const_iterator 
	Node2D::get_location( const std::vector<std::pair<double,double>>& nodeLocations ) const
{
	std::vector<std::pair<double,double>>::const_iterator locIt = nodeLocations.begin() + nodeNum_;
	return locIt;
};

////////////////////////////////////////////////////////////////
// Mesh Element Class

class MeshElement2D
{
  public:
	MeshElement2D(int numNodes = 0);
	MeshElement2D( const std::shared_ptr<FiniteElement2D>& masterElement, 
		const std::vector<Node2D>& nodes);

	unsigned int num_nodes() const;
	const std::shared_ptr<FiniteElement2D>& get_master_element() const;
	void set_master_element( const std::shared_ptr<FiniteElement2D>& masterElement );
	void set_node_number( const unsigned int& numNodes );

	Node2D& operator[] (const unsigned int& i );
	const Node2D& operator[] ( const unsigned int& i) const;

  private:
	std::shared_ptr<FiniteElement2D> masterElement_;
	std::vector<Node2D> nodes_;
};

MeshElement2D::MeshElement2D(int numNodes)
		:nodes_(numNodes)
{};

MeshElement2D::MeshElement2D(const std::shared_ptr<FiniteElement2D>& masterElement, 
		const std::vector<Node2D>& nodes)
		: masterElement_(masterElement), nodes_(nodes)
{};

void MeshElement2D::set_master_element( const std::shared_ptr<FiniteElement2D>& masterElement )
{
	masterElement_ = masterElement;
};

const std::shared_ptr<FiniteElement2D>& MeshElement2D::get_master_element() const
{
	return masterElement_;
};

unsigned int MeshElement2D::num_nodes() const
{
	return nodes_.size();
};

Node2D& MeshElement2D::operator[] (const unsigned int& i )
{
	return nodes_[i];
};
	
const Node2D& MeshElement2D::operator[] ( const unsigned int& i) const
{
	return nodes_[i];
};

void MeshElement2D::set_node_number( const unsigned int& numNodes )
{
	if( nodes_.size() != numNodes )
		nodes_.resize(numNodes);
};

//////////////////////////////////////////////////////////////////////////////////////
// Mesh Class

Mesh2D::Mesh2D( const std::shared_ptr<FiniteElement2D>& masterElement,
		  const std::vector<std::pair<double,double>>& nodeLocations,
		  const std::vector<std::vector<unsigned int>>& nodeAdjacency,
		  const std::vector<std::vector<unsigned int>>& nodesInElement,
		  const std::vector<std::vector<unsigned int>>&nodeMapToMasterElem)
		  :masterElement_(masterElement), nodeLocations_(nodeLocations),
		  nodeAdjacency_(nodeAdjacency_), nodesInElement_(nodesInElement),
		  //meshElements_(nodesInElement.size()), 
		  numElements_(nodesInElement.size()),
		  nodeMapToMasterElem_(nodeMapToMasterElem)
{
	create_mesh_elements();
};


void Mesh2D::create_mesh_elements()
{
	/*
	for ( unsigned int elemCtr = 0; elemCtr < numElements_; ++elemCtr ) {
		
		unsigned int numNodes = nodesInElement_[elemCtr].size();
		meshElements_[elemCtr].set_master_element(masterElement_);
		meshElements_[elemCtr].set_node_number( numNodes );

		auto nodePtr = nodesInElement_[elemCtr].begin();

		for( unsigned int nodeCtr = 0; nodeCtr < numNodes; ++nodeCtr ) {
			meshElements_[elemCtr][nodeCtr].set_node_num(*nodePtr);
			nodePtr++;
		}
		
	}
	*/
};

unsigned int Mesh2D::num_elements() const
{
	return numElements_;
};

const std::vector<unsigned int>& Mesh2D::get_nodes_in_element( unsigned int elem) const
{
	return nodesInElement_[elem];
};

const std::pair<double,double>& Mesh2D::get_node_location( unsigned int node ) const
{
	return nodeLocations_[node];	
};

unsigned int Mesh2D::get_node_map_to_master( unsigned int elem, unsigned int node) const
{
	const std::vector<unsigned int>& nodes = nodeMapToMasterElem_[elem];

	unsigned int pos = 0;

	while( nodes[pos] != node )
		pos++;

	return pos;
};

unsigned int Mesh2D::numNodes() const
{
	return nodeLocations_.size();
};