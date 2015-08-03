#include <Quadrature.h>

#include <cmath>

Quadrature::Quadrature( const size_t& numDims, const size_t& pointsPerDim,
					   const QuadratureGenerator& quadGen)
	:numDims_(numDims), pointsPerDim_(pointsPerDim), 
	weights_(static_cast<size_t>(std::pow(pointsPerDim,numDims)),0.0),
	points_(static_cast<size_t>(std::pow(pointsPerDim,numDims)),std::vector<double>(numDims,0.0))
{
	initialize_quad_info(quadGen);
};

size_t Quadrature::num_dims() const
{
	return numDims_;	
};

size_t Quadrature::points_per_dim() const
{
	return pointsPerDim_;
};

size_t Quadrature::size() const
{
	return numDims_*pointsPerDim_;
};

const std::vector<double>& Quadrature::get_weights() const
{
	return weights_;
};

const double& Quadrature::get_weight(size_t i) const
{
	return weights_[i];
};

const std::vector<std::vector<double>>& Quadrature::get_points() const
{
	return points_;
};
	
const std::vector<double>& Quadrature::get_point(size_t i) const
{
	return points_[i];
};

void Quadrature::initialize_quad_info(const QuadratureGenerator& quadGen)
{
	const std::vector<double>& weights = quadGen.get_weights(pointsPerDim_);
	const std::vector<double>& points = quadGen.get_points(pointsPerDim_);

	if( numDims_ == 2 )
	{
		for( unsigned int xPoint = 0; xPoint < pointsPerDim_; ++ xPoint )
		{
			for( unsigned int yPoint = 0; yPoint < pointsPerDim_; ++yPoint )
			{
				weights_[xPoint + yPoint*pointsPerDim_] = weights[xPoint]*weights[yPoint];
				points_[xPoint + yPoint*pointsPerDim_][0] = points[xPoint]; 
				points_[xPoint + yPoint*pointsPerDim_][1] = points[yPoint]; 
			}
		}
	} else if( numDims_ == 1 ) {
		for( unsigned int xPoint = 0; xPoint < pointsPerDim_; ++ xPoint )
		{
			weights_[xPoint] = weights[xPoint];
			points_[xPoint][0] = points[xPoint];
		}
	} else if( numDims_ == 3 ) {
		//TODO
	};
};

