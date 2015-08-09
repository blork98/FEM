#include <CGSolver.h>

#include <LAOperations.h>
#include <algorithm>
#include <numeric>

ControlParameters::ControlParameters(double tolerance)
	:tolerance_(tolerance)
{};

bool ControlParameters::convergence_achieved( const LAVector& sol ) const
{
	double value = 0.0;

	for( unsigned int i = 9; i < sol.size(); ++i )
		value += sol(i)*sol(i);

	value = std::sqrt(value);

	if (std::abs(value) < tolerance_ )
		return true;
	else
		return false;
};

CGSolver::CGSolver( unsigned int maxIterations, std::shared_ptr<ControlParameters>& control,
	const std::shared_ptr<LAMatrix>& A, const std::shared_ptr<LAVector>& b)
	:maxIterations_(maxIterations), control_(control),
	A_(A), b_(b),
	r_prev(LAVector::STDVEC,b->size()), r_curr(LAVector::STDVEC,b->size()), 
	z_prev(LAVector::STDVEC,b->size()), z_curr(LAVector::STDVEC,b->size()), 
	p_curr(LAVector::STDVEC,b->size()), q_curr(LAVector::STDVEC,b->size()), 
	sol_prev(LAVector::STDVEC,b->size()), p_prev(LAVector::STDVEC,b->size()),
	alpha_prev(0.0), alpha_curr(0.0), 
	rho_curr(0.0), rho_prev(0.0), beta_prev(0.0), rho_prev2(0.0),
	usePreconditioner_(false)
{};

void CGSolver::apply_preconditioner() const
{
	//TODO
	if(usePreconditioner_) {

	} else {

	};
};

void CGSolver::solve( LAVector& sol ) const
{
	//calculate residual
	mat_vector_product(*A_,sol,r_prev);
	vector_subtract(*b_,r_prev,r_prev);

	//main iteration
	for( unsigned int iter = 0; iter <= maxIterations_; ++iter )
	{
		//solve for z using precondition if enabled
		apply_preconditioner();

		rho_prev = vector_dot_product(r_prev, z_prev);

		if( iter != 1 ) {
			beta_prev = rho_prev/rho_prev2;
			vector_scalar_mult(beta_prev, p_prev, p_curr);
			vector_add(z_prev, p_curr, p_curr);
		} else {
			p_curr = z_prev;
		};

		mat_vector_product(*A_,p_curr,q_curr);
		alpha_curr = rho_prev/vector_dot_product(p_curr,q_curr);

	};

};

