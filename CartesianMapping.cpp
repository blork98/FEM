#include <CartesianMapping.h>

BilinearQuadMapping::BilinearQuadMapping( const std::vector<std::vector<double>>& nodeLocations)
	:nodeLocations_(nodeLocations), numNodes_(nodeLocations.size())
{};

void BilinearQuadMapping::transform_real_to_master( const std::vector<double>& rPoint, 
													std::vector<double>& mPoint) const
{


	for( size_t dim = 0; dim < mPoint.size(); ++dim) 
	{
		mPoint[dim] = 0.0;
		for( size_t nodeLoc = 0; nodeLoc < numNodes_; ++ nodeLoc)
		{
			mPoint[dim];
		};
	}
};

void BilinearQuadMapping::transform_master_to_real( const std::vector<double>& mPoint, 
													std::vector<double>& rPoint) const
{

};