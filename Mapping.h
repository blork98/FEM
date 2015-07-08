#ifndef MAPPING_H_
#define MAPPING_H_

#include <vector>

class Mapping
{
public:
	Mapping(const unsigned int& dim);

	virtual void transform_real_to_master( 
		const std::vector<double>& rPoint, std::vector<double>& mPoint) const = 0;
	virtual void transform_master_to_real( 
		const std::vector<double>& mPoint, std::vector<double>& rPoint) const= 0;
	virtual void get_jacobian_matrix( 
		std::vector<double>& jMat, double& jacobian) const = 0;
	virtual void set_node_locations_master( const std::vector<std::pair<double,double> >& nodeLocations) = 0;
	virtual void set_point(const std::vector<double>& evalPoint) = 0;
    virtual void set_node_locations( const std::vector<std::pair<double,double> >& nodeLocations) = 0;

	const unsigned int& dim() const;
private:
	unsigned int dim_;
};

#endif