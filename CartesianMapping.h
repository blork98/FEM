#ifndef CARTESIAN_MAPPING_H_
#define CARTESIAN_MAPPING_H_

#include <Mapping.h>

class BilinearQuadMapping : public Mapping 
{
public:
	BilinearQuadMapping( const std::vector<std::vector<double>>& nodeLocations);

	virtual void transform_real_to_master( const std::vector<double>& rPoint, 
										std::vector<double>& mPoint) const;
	virtual void transform_master_to_real( const std::vector<double>& mPoint, 
										std::vector<double>& rPoint) const;

private:
	std::vector<std::vector<double>> nodeLocations_;
	size_t numNodes_;
};

#endif