#ifndef CARTESIAN_MAPPING_H_
#define CARTESIAN_MAPPING_H_

#include <Mapping.h>

class BilinearQuadMapping2D : public Mapping 
{
public:
	BilinearQuadMapping2D( const std::vector<std::pair<double,double>>& nodeLocations);

	virtual void transform_real_to_master( const std::vector<double>& rPoint, 
										std::vector<double>& mPoint) const;
	virtual void transform_master_to_real( const std::vector<double>& mPoint, 
										std::vector<double>& rPoint) const;

private:
	double shape_value(	const unsigned int& node, 
						const std::pair<double,double>& point) const;
	std::pair<double,double> shape_grad_value( const unsigned int& node, 
											const std::pair<double,double>& point) const;

	std::vector<std::pair<double,double>> nodeLocations_;
	size_t numNodes_;
};

#endif