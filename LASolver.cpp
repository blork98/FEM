#include <LASolver.h>

BoostLUSolver::BoostLUSolver( const LAVector& rhs, const LAMatrix& A)
	: rhs_(rhs.size(),0.0), A_(A.num_rows(), A.num_cols(),0.0),
	pm(A_.size1()), sol_(rhs.size(),0.0)
{
	vector_to_ublasvec(rhs);
	matrix_to_ublasmat(A);
	factorize();
};

void BoostLUSolver::vector_to_ublasvec( const LAVector& rhs)
{
	if( rhs.size() != rhs_.size() )
		rhs_.resize(rhs.size());

	for( unsigned int i = 0; i < rhs.size(); ++i)
		rhs_(i) = rhs(i);
};

void BoostLUSolver::matrix_to_ublasmat( const LAMatrix& A)
{
	if( A.num_rows() != A_.size1() || A.num_cols() != A_.size2() )
		A_.resize(A.num_rows(), A.num_cols());

	for( unsigned int i = 0; i < A.num_rows(); ++i )
	{
		for( unsigned int j = 0; j < A.num_cols(); ++j )
			A_(i,j) = A(i,j);
	};
};

void BoostLUSolver::set_b(const std::shared_ptr<LAVector>& b)
{
	vector_to_ublasvec(*b);
};

void BoostLUSolver::set_A(const std::shared_ptr<LAMatrix>& A)
{
	matrix_to_ublasmat(*A);
	factorize();
};

void BoostLUSolver::factorize()
{
	pm = boost::numeric::ublas::permutation_matrix<size_t> (A_.size1());
	boost::numeric::ublas::lu_factorize(A_,pm);
};

void  BoostLUSolver::solve( LAVector& sol )
{
	boost::numeric::ublas::lu_substitute(A_,pm,sol_);

	for( unsigned int i = 0; i < sol.size(); ++i)
		sol(i) = sol_(i);
};