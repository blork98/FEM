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
	MeshElement2D( const boost::shared_ptr<FiniteElement2D>& masterElement, 
		const std::vector<Node2D>& nodes);

	unsigned int num_nodes() const;
	const boost::shared_ptr<FiniteElement2D>& get_master_element() const;
	void set_master_element( const boost::shared_ptr<FiniteElement2D>& masterElement );
	void set_node_number( const unsigned int& numNodes );

	Node2D& operator[] (const unsigned int& i );
	const Node2D& operator[] ( const unsigned int& i) const;

  private:
	boost::shared_ptr<FiniteElement2D> masterElement_;
	std::vector<Node2D> nodes_;
};

MeshElement2D::MeshElement2D(int numNodes)
		:nodes_(numNodes)
{};

MeshElement2D::MeshElement2D(const boost::shared_ptr<FiniteElement2D>& masterElement, 
		const std::vector<Node2D>& nodes)
		: masterElement_(masterElement), nodes_(nodes)
{};

void MeshElement2D::set_master_element( const boost::shared_ptr<FiniteElement2D>& masterElement )
{
	masterElement_ = masterElement;
};

const boost::shared_ptr<FiniteElement2D>& MeshElement2D::get_master_element() const
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

Mesh2D::Mesh2D( const boost::shared_ptr<FiniteElement2D>& masterElement,
		  const std::vector<std::pair<double,double>>& nodeLocations,
		  const std::vector<std::list<unsigned int>>& nodeAdjacency,
		  const std::vector<std::list<unsigned int>>& nodesInElement)
		  :masterElement_(masterElement), nodeLocations_(nodeLocations),
		  nodeAdjacency_(nodeAdjacency_), nodesInElement_(nodesInElement),
		  meshElements_(nodesInElement.size(), MeshElement2D(nodesInElement[0].size())), 
		  numElements_(nodesInElement.size())
{
	create_mesh_elements();
};

void Mesh2D::create_mesh_elements()
{
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
};