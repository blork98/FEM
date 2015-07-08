#ifndef DATA_H_
#define DATA_H_

#include <utility>

class Data2D
{
public:
	virtual double k_val( const std::pair<double,double>& point ) const = 0;
	virtual double b_val( const std::pair<double,double>& point ) const = 0;
	virtual double f_val( const std::pair<double,double>& point ) const = 0;
	virtual double p_val( const std::pair<double,double>& point ) const = 0;
	virtual double y_val( const std::pair<double,double>& point ) const = 0;
};

class ConstantData2D : public Data2D
{
public:
	ConstantData2D( const double& k, const double& b,
		const double f, const double p,
		const double y);

	virtual double k_val( const std::pair<double,double>& point ) const;
	virtual double b_val( const std::pair<double,double>& point ) const;
	virtual double f_val( const std::pair<double,double>& point ) const;
	virtual double p_val( const std::pair<double,double>& point ) const;
	virtual double y_val( const std::pair<double,double>& point ) const;

	void set_constants( const double& k, const double& b,
		const double& f, const double& p, const double& y);

private:
	double k_, b_, f_, p_, y_;
};

#endif