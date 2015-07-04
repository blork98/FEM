#include <CartesianMapping.h>

BilinearQuadMapping2D::BilinearQuadMapping2D( 
    const std::vector<std::pair<double,double>>& nodeLocationsMaster)
	:Mapping(2), nodeLocationsMaster_(nodeLocationsMaster), numNodes_(4),
    cachedVals_(4,0.0), nodeLocations_(4,std::make_pair(0.0,0.0))
{};

void BilinearQuadMapping2D::get_jacobian_matrix(
    std::vector<double>& jMat, double& detJ) const
{
    detJ = jacobian(evalLocation_);

    jMat[0] = cachedVals_[3]/detJ;
    jMat[1] = -1*cachedVals_[1]/detJ;
    jMat[2] = -1*cachedVals_[2]/detJ;
    jMat[3] = cachedVals_[0]/detJ;
};

void BilinearQuadMapping2D::set_point(
    const std::vector<double>& evalPoint)
{
    evalLocation_.first = evalPoint[0];
    evalLocation_.second = evalPoint[1];
    calculate_cached_values(evalLocation_);
};

void BilinearQuadMapping2D::set_node_locations(
    const std::vector<std::pair<double,double>>& nodeLocations)
{    
    nodeLocations_ = nodeLocations;
};

void BilinearQuadMapping2D::set_node_locations_master(
    const std::vector<std::pair<double,double>>& nodeLocations)
{    
    nodeLocationsMaster_ = nodeLocations;
};


void BilinearQuadMapping2D::reset_vals()
{
    for( unsigned int nodeCtr = 0; nodeCtr <  numNodes_; ++nodeCtr)
        cachedVals_[nodeCtr] = 0;
};

void BilinearQuadMapping2D::calculate_cached_values(
    const std::pair<double,double>& point)
{
    std::pair<double,double>  gradVals = std::make_pair(0.0,0.0);
    reset_vals();
    
    for( unsigned int nodeCtr = 0; nodeCtr < numNodes_; ++nodeCtr)
    {
        gradVals = shape_grad_value(nodeCtr,point);
        cachedVals_[0] += nodeLocations_[nodeCtr].first * gradVals.first;
        cachedVals_[1] += nodeLocations_[nodeCtr].first * gradVals.second;
        cachedVals_[2] += nodeLocations_[nodeCtr].second * gradVals.first;
        cachedVals_[3] += nodeLocations_[nodeCtr].second * gradVals.second;
    }
};

double BilinearQuadMapping2D::jacobian(
    const std::pair<double,double>& point) const
{
    double j = 0.0;
    
    //std::pair<double,double> ePoint = std::make_pair(point[0],point[1]);
    
    //calculate_cached_values(ePoint);
    j = cachedVals_[0]*cachedVals_[3] - cachedVals_[1]*cachedVals_[2];
    
    return j;
};

void BilinearQuadMapping2D::transform_real_to_master( 
    const std::vector<double>& rPoint, std::vector<double>& mPoint) const
{
    //TODO: Not Really necessary
};

void BilinearQuadMapping2D::transform_master_to_real( 
    const std::vector<double>& mPoint, std::vector<double>& rPoint) const
{
	std::pair<double,double> point = std::make_pair(mPoint[0],mPoint[1]);
	double nodeValue = 0.0;

	for( unsigned int dimCtr = 0; dimCtr < dim(); ++dimCtr) 
	{
		rPoint[dimCtr] = 0.0;
        
		for( unsigned int nodeLoc = 0; nodeLoc < numNodes_; ++ nodeLoc)
		{
			if ( dimCtr == 0 )
				nodeValue = nodeLocations_[nodeLoc].first;
			else 
				nodeValue = nodeLocations_[nodeLoc].second;

			rPoint[dimCtr] += shape_value(nodeLoc,point)*nodeValue;
		};
	};
};

double BilinearQuadMapping2D::shape_value( 
    const unsigned int& node, const std::pair<double,double>& point) const
{
	double value = 0.0, normalizer = 0.0;
	double x0 = 0.0, y0 = 0.0;

	switch(node) {
		case 0:
			x0 = nodeLocationsMaster_[1].first;
			y0 = nodeLocationsMaster_[3].second;
			normalizer = 1/((x0 - nodeLocationsMaster_[0].first)*(y0 - nodeLocationsMaster_[0].second ));
			value = normalizer*(x0 - point.first)*(y0 - point.second);
			break;
		case 1:
			x0 = nodeLocationsMaster_[0].first;
			y0 = nodeLocationsMaster_[2].second;
			normalizer = 1/((x0 - nodeLocationsMaster_[1].first)*(y0 - nodeLocationsMaster_[1].second ));
			value = normalizer*(x0 - point.first)*(y0 - point.second);
			break;
		case 2:
			x0 = nodeLocationsMaster_[3].first;
			y0 = nodeLocationsMaster_[1].second;
			normalizer = 1/((x0 - nodeLocationsMaster_[2].first)*(y0 - nodeLocationsMaster_[2].second ));
			value = normalizer*(x0 - point.first)*(y0 - point.second);
			break;
		case 3:
			x0 = nodeLocationsMaster_[2].first;
			y0 = nodeLocationsMaster_[0].second;
			normalizer = 1/((x0 - nodeLocationsMaster_[3].first)*(y0 - nodeLocationsMaster_[3].second ));
			value = normalizer*(x0 - point.first)*(y0 - point.second);
			break;
		default:
			break;
	};

	return value;
};

std::pair<double,double> BilinearQuadMapping2D::shape_grad_value( 
    const unsigned int& node, const std::pair<double,double>& point) const
{
	std::pair<double,double> value = std::make_pair(0.0,0.0);
	double x0 = 0.0, y0 = 0.0, normalizer = 0.0;

	switch(node) {
		case 0:
			x0 = nodeLocationsMaster_[1].first;
			y0 = nodeLocationsMaster_[3].second;
			normalizer = 1/((x0 - nodeLocationsMaster_[0].first)*(y0 - nodeLocationsMaster_[0].second ));
			//value = normalizer*(x0 - point.first)*(y0 - point.second);
			value.first = normalizer*(-1)*(y0 - point.second);
			value.second = normalizer*(x0 - point.first)*(-1);
			break;
		case 1:
			x0 = nodeLocationsMaster_[0].first;
			y0 = nodeLocationsMaster_[2].second;
			normalizer = 1/((x0 - nodeLocationsMaster_[1].first)*(y0 - nodeLocationsMaster_[1].second ));
			//value = normalizer*(x0 - point.first)*(y0 - point.second);
			value.first = normalizer*(-1)*(y0 - point.second);
			value.second = normalizer*(x0 - point.first)*(-1);
			break;
		case 2:
			x0 = nodeLocationsMaster_[3].first;
			y0 = nodeLocationsMaster_[1].second;
			normalizer = 1/((x0 - nodeLocationsMaster_[2].first)*(y0 - nodeLocationsMaster_[2].second ));
			//value = normalizer*(x0 - point.first)*(y0 - point.second);
			value.first = normalizer*(-1)*(y0 - point.second);
			value.second = normalizer*(x0 - point.first)*(-1);
			break;
		case 3:
			x0 = nodeLocationsMaster_[2].first;
			y0 = nodeLocationsMaster_[0].second;
			normalizer = 1/((x0 - nodeLocationsMaster_[3].first)*(y0 - nodeLocationsMaster_[3].second ));
			//value = normalizer*(x0 - point.first)*(y0 - point.second);
			value.first = normalizer*(-1)*(y0 - point.second);
			value.second = normalizer*(x0 - point.first)*(-1);
			break;
		default:
			break;
	};

	return value;
};