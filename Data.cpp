#include <Data.h>

ConstantData2D::ConstantData2D( const double& k, 
	const double& b, const double f, 
	const double p, const double y)
	: k_(k), b_(b), f_(f), p_(p), y_(y)
{};

double ConstantData2D::k_val( const std::pair<double,double>& point ) const
{
	return k_;
};

double ConstantData2D::b_val( const std::pair<double,double>& point ) const
{
	return b_;
};

double ConstantData2D::f_val( const std::pair<double,double>& point ) const
{
	return f_;
};

double ConstantData2D::p_val( const std::pair<double,double>& point ) const
{
	return p_;
};

double ConstantData2D::y_val( const std::pair<double,double>& point ) const
{
	return y_;
};

void ConstantData2D::set_constants( const double& k, const double& b,
	const double& f, const double& p, const double& y)
{
	k_ = k;
	b_ = b;
	f_ = f;
	p_ = p;
	y_ = y;
};