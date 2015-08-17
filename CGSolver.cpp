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

	for( unsigned int i = 0; i < sol.size(); ++i )
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

void CGSolver::apply_preconditioner(LAVector* rPrev) const
{
	//TODO
	if(usePreconditioner_) {

	} else {
		z_prev = *rPrev;
	};
};

void CGSolver::solve( LAVector& sol ) 
{
	//local vars
	LAVector *rPrev, *rCurr, *pCurr, *pPrev, *solPrev, *solCurr;
	rPrev = &r_prev;
	rCurr = &r_curr;
	pCurr = &p_curr;
	pPrev = &p_prev;

	sol_prev = sol;
	solPrev = &sol_prev;
	solCurr = &sol;

	//calculate initial residual
	mat_vector_product(*A_,sol,r_prev);
	vector_subtract(*b_,r_prev,r_prev);

	//main iteration
	for( unsigned int iter = 1; iter <= maxIterations_; ++iter )
	{
		//solve for z using precondition if enabled
		apply_preconditioner(rPrev);//error here

		rho_prev = vector_dot_product(*rPrev, z_prev);

		if( iter != 1 ) {
			beta_prev = rho_prev/rho_prev2;
			vector_axpy(beta_prev, *pPrev, z_prev, *pCurr);	
		} else {
			*pCurr = z_prev;
		};

		mat_vector_product(*A_,*pCurr,q_curr);
		alpha_curr = rho_prev/vector_dot_product(*pCurr,q_curr);

		vector_axpy(alpha_curr, *pCurr, *solPrev, *solCurr );
		vector_xmay(alpha_curr, q_curr, *rPrev, *rCurr);

		//check for convergence
		if( control_->convergence_achieved(*rCurr) ) {
			if( (iter % 2) == 0)
				sol = sol_prev;

			break;
		};

		//update prev variables
		rho_prev2 = rho_prev;
		std::swap(rPrev,rCurr);
		std::swap(pPrev,pCurr);
		std::swap(solPrev, solCurr);
	};

};

