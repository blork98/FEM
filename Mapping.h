#ifndef MAPPING_H_
#define MAPPING_H_

#include <vector>

class Mapping
{
public:
	virtual void transform_real_to_master( const std::vector<double>& rPoint, 
										std::vector<double>& mPoint) const = 0;
	virtual void transform_master_to_real( const std::vector<double>& mPoint, 
										std::vector<double>& rPoint) const= 0;
};

#endif