#ifndef QUADRATURE_GENERATOR_H_
#define QUADRATURE_GENERATOR_H_

#include <map>
#include <vector>

class QuadratureGenerator //: public QuantLib::Singleton<QuadratureGenerator>
{
	//friend class QuantLib::Singleton<QuadratureGenerator>;
public:
	QuadratureGenerator();
	const std::pair<std::vector<double>,std::vector<double>>& 
		get_info( size_t numQuadPoints ) const;
	const std::vector<double>& get_weights( size_t numQuadPoints ) const;
	const std::vector<double>& get_points(size_t numQuadPoints ) const;

private:
	void initialize();

	std::map<int,std::pair<std::vector<double>,std::vector<double>>> data_;
	mutable std::map<int,std::pair<std::vector<double>,std::vector<double>>>::const_iterator dataIt;
};

#endif

