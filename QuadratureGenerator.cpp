#include <QuadratureGenerator.h>

QuadratureGenerator::QuadratureGenerator()
{
	initialize();
	dataIt = data_.end();
};

void QuadratureGenerator::initialize()
{
	//for n = 0 Error Data
	{
		data_[0] = std::make_pair(std::vector<double>(0),std::vector<double>(0));
	}
	//for n = 2
	{
		std::vector<double> w(2,1.0000000000000000);
		std::vector<double> r(2,0.5773502691896257);
		r[0] *= -1.00000;
		data_[2] = std::make_pair(r,w);
	}
	//for n = 3
	{
		std::vector<double> w(3,0.0000000000000000);
		std::vector<double> r(3,0.0000000000000000);
		w[0] = 0.8888888888888888;
		w[1] = 0.5555555555555556;	
		w[2] = 0.5555555555555556;
		r[0] = 0.0000000000000000;
		r[1] = -0.7745966692414834;
		r[2] = 0.7745966692414834;
		data_[3] = std::make_pair(r,w);
	}
	//for n = 4;
	{
		std::vector<double> w(4,0.0000000000000000);
		std::vector<double> r(4,0.0000000000000000);
		w[0] = 0.6521451548625461;
		w[1] = 0.6521451548625461;	
		w[2] = 0.3478548451374538;
		w[3] = 0.3478548451374538;
		r[0] = -0.3399810435848563;
		r[1] = 0.3399810435848563;
		r[2] = -0.8611363115940526;
		r[3] = 0.8611363115940526;
		data_[4] = std::make_pair(r,w);
	}
	//for n = 8
	{
		std::vector<double> w(8,0.0000000000000000);
		std::vector<double> r(8,0.0000000000000000);
		w[0] = 0.3626837833783620;
		w[1] = 0.3626837833783620;	
		w[2] = 0.3137066458778873;
		w[3] = 0.3137066458778873;
		w[4] = 0.2223810344533745;
		w[5] = 0.2223810344533745;	
		w[6] = 0.1012285362903763;
		w[7] = 0.1012285362903763;
		r[0] = -0.1834346424956498;
		r[1] = 0.1834346424956498;
		r[2] = -0.5255324099163290;
		r[3] = 0.5255324099163290;
		r[4] = -0.7966664774136267;
		r[5] = 0.7966664774136267;
		r[6] = -0.9602898564975363;
		r[7] = 0.9602898564975363;
		data_[8] = std::make_pair(r,w);
	}
};

const std::pair<std::vector<double>,std::vector<double>>& 
	QuadratureGenerator::get_info( size_t numQuadPoints ) const
{
	dataIt = data_.find(numQuadPoints);

	if( dataIt == data_.end() ) 
	{
		dataIt = data_.find(0);
	}

	return dataIt->second;
};

const std::vector<double>& QuadratureGenerator::get_weights( size_t numQuadPoints ) const
{
	dataIt = data_.find(numQuadPoints);

	if( dataIt == data_.end() ) 
	{
		dataIt = data_.find(0);
	}

	return dataIt->second.second;
};
	
const std::vector<double>& QuadratureGenerator::get_points(size_t numQuadPoints ) const
{
	dataIt = data_.find(numQuadPoints);

	if( dataIt == data_.end() ) 
	{
		dataIt = data_.find(0);
	}

	return dataIt->second.first;
};
