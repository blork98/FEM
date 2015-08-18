#include <Preconditioner.h>

Preconditioner::Preconditioner(const std::shared_ptr<LAVector>& b, const std::shared_ptr<LAMatrix>& A,
		const std::shared_ptr<LinearSolver>& solver)
		:b_(b), solver_(solver), M_(nullptr)
{
	M_ = std::make_shared<LAMatrix>(LAMatrix::STDMAT, A->num_rows(), A->num_cols());
};

void Preconditioner::solve( LAVector& sol)
{
	//note add set A and set rhs to linear solver
	solver_-> set_b(b_);
	solver_-> set_A(M_);
	solver_->solve(sol);
};

JacobiPC::JacobiPC(const std::shared_ptr<LAVector>& b, const std::shared_ptr<LAMatrix>& A,
		const std::shared_ptr<LinearSolver>& solver)
		:Preconditioner(b,A,solver)
{
    create_precondioner(A);    
};

void JacobiPC::create_precondioner(const std::shared_ptr<LAMatrix>& A)
{
	if( A->num_cols() != A-> num_rows() )
		throw;

	for( unsigned int i = 0; i < A->num_cols(); ++i )
		(*M_)(i,i) = (*A)(i,i);
};

void JacobiPC::solve( LAVector& sol)
{
	if( (*M_).num_cols() != (*b_).size() )
		throw;

	if( sol.size() != (*b_).size() )
		sol = LAVector(sol.container_type(), (*b_).size());

	for( unsigned int i = 0; i < (*b_).size(); ++i )
		sol(i) = (*b_)(i)/(*M_)(i,i);
};