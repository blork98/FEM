#ifndef LASOLVER_H_
#define LASOLVER_H_

#include <LAContainers.h>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/lu.hpp>

class LinearSolver 
{
public:
	virtual void solve( LAVector& sol ) = 0;
};

class BoostLUSolver : public LinearSolver
{
public:
	BoostLUSolver( const LAVector& rhs, const LAMatrix& A);

	void solve( LAVector& sol);
	void set_rhs( const LAVector& rhs);
	void set_linear_system( const LAMatrix& A);

private:
	void factorize();
	void vector_to_ublasvec( const LAVector& rhs);
	void matrix_to_ublasmat( const LAMatrix& A);

	boost::numeric::ublas::vector<double> rhs_, sol_;
	boost::numeric::ublas::matrix<double> A_;
	boost::numeric::ublas::permutation_matrix<size_t> pm;
};

#endif