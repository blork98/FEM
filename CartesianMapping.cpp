#include <CartesianMapping.h>

BilinearQuadMapping2D::BilinearQuadMapping2D( const std::vector<std::pair<double,double>>& nodeLocations)
	:Mapping(2), nodeLocations_(nodeLocations), numNodes_(nodeLocations.size())
{};

void BilinearQuadMapping2D::transform_real_to_master( const std::vector<double>& rPoint, 
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

void BilinearQuadMapping2D::transform_master_to_real( const std::vector<double>& mPoint, 
													std::vector<double>& rPoint) const
{
	std::pair<double,double> point = std::make_pair(mPoint[0],mPoint[1]);
	double nodeValue = 0.0;

	for( unsigned int dimCtr = 0; dimCtr < dim(); ++dimCtr) 
	{
		rPoint[dimCtr] = 0.0;
		for( size_t nodeLoc = 0; nodeLoc < numNodes_; ++ nodeLoc)
		{
			if ( dimCtr == 0 )
				nodeValue = nodeLocations_[nodeLoc].first;
			else 
				nodeValue = nodeLocations_[nodeLoc].second;

			rPoint[dimCtr] += shape_value(nodeLoc,point)*nodeValue;
		};
	};
};

double BilinearQuadMapping2D::shape_value( const unsigned int& node, 
										const std::pair<double,double>& point) const
{
	double value = 0.0, normalizer = 0.0;
	double x0 = 0.0, y0 = 0.0;

	switch(node) {
		case 0:
			x0 = nodeLocations_[1].first;
			y0 = nodeLocations_[3].second;
			normalizer = 1/((x0 - nodeLocations_[0].first)*(y0 - nodeLocations_[0].second ));
			value = normalizer*(x0 - point.first)*(y0 - point.second);
			break;
		case 1:
			x0 = nodeLocations_[0].first;
			y0 = nodeLocations_[2].second;
			normalizer = 1/((x0 - nodeLocations_[1].first)*(y0 - nodeLocations_[1].second ));
			value = normalizer*(x0 - point.first)*(y0 - point.second);
			break;
		case 2:
			x0 = nodeLocations_[3].first;
			y0 = nodeLocations_[1].second;
			normalizer = 1/((x0 - nodeLocations_[2].first)*(y0 - nodeLocations_[2].second ));
			value = normalizer*(x0 - point.first)*(y0 - point.second);
			break;
		case 3:
			x0 = nodeLocations_[2].first;
			y0 = nodeLocations_[0].second;
			normalizer = 1/((x0 - nodeLocations_[3].first)*(y0 - nodeLocations_[3].second ));
			value = normalizer*(x0 - point.first)*(y0 - point.second);
			break;
		default:
			break;
	};

	return value;
};

std::pair<double,double> BilinearQuadMapping2D::shape_grad_value( const unsigned int& node, 
											const std::pair<double,double>& point) const
{
	std::pair<double,double> value = std::make_pair(0.0,0.0);
	double x0 = 0.0, y0 = 0.0, normalizer = 0.0;

	switch(node) {
		case 0:
			x0 = nodeLocations_[1].first;
			y0 = nodeLocations_[3].second;
			normalizer = 1/((x0 - nodeLocations_[0].first)*(y0 - nodeLocations_[0].second ));
			//value = normalizer*(x0 - point.first)*(y0 - point.second);
			value.first = normalizer*(-1)*(y0 - point.second);
			value.second = normalizer*(x0 - point.first)*(-1);
			break;
		case 1:
			x0 = nodeLocations_[0].first;
			y0 = nodeLocations_[2].second;
			normalizer = 1/((x0 - nodeLocations_[1].first)*(y0 - nodeLocations_[1].second ));
			//value = normalizer*(x0 - point.first)*(y0 - point.second);
			value.first = normalizer*(-1)*(y0 - point.second);
			value.second = normalizer*(x0 - point.first)*(-1);
			break;
		case 2:
			x0 = nodeLocations_[3].first;
			y0 = nodeLocations_[1].second;
			normalizer = 1/((x0 - nodeLocations_[2].first)*(y0 - nodeLocations_[2].second ));
			//value = normalizer*(x0 - point.first)*(y0 - point.second);
			value.first = normalizer*(-1)*(y0 + point.second);
			value.second = normalizer*(x0 + point.first)*(-1);
			break;
		case 3:
			x0 = nodeLocations_[2].first;
			y0 = nodeLocations_[0].second;
			normalizer = 1/((x0 - nodeLocations_[3].first)*(y0 - nodeLocations_[3].second ));
			//value = normalizer*(x0 - point.first)*(y0 - point.second);
			value.first = normalizer*(-1)*(y0 + point.second);
			value.first = normalizer*(x0 - point.first)*(-1);
			break;
		default:
			break;
	};

	return value;
};