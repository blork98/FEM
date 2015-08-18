#ifndef CGSOLVER_H_
#define CGSOLVER_H_

#include<LASolver.h>

class ControlParameters
{
public:
	ControlParameters(double tolerance);
	virtual bool convergence_achieved( const LAVector& sol ) const;

private:
	double tolerance_;
};

class CGSolver : public LinearSolver 
{
public:
	CGSolver( unsigned int maxIterations, std::shared_ptr<ControlParameters>& control,
		const std::shared_ptr<LAMatrix>& A, const std::shared_ptr<LAVector>& b);
	void solve( LAVector& sol );
	void apply_preconditioner(LAVector* rPrev) const;

	void set_A(const std::shared_ptr<LAMatrix>& A);
	void set_b(const std::shared_ptr<LAVector>& b);
	
private:
	std::shared_ptr<ControlParameters> control_;
	std::shared_ptr<LAMatrix> A_;
	std::shared_ptr<LAVector> b_;
	unsigned int maxIterations_;
	mutable LAVector r_prev, r_curr, z_prev, z_curr, p_curr, p_prev, q_curr, sol_prev;
	mutable double alpha_prev, alpha_curr, rho_curr, rho_prev, rho_prev2, beta_prev;
	bool usePreconditioner_;
};

class BCGSolver : public LinearSolver
{
public:
	BCGSolver( unsigned int maxIterations, std::shared_ptr<ControlParameters>& control,
		const std::shared_ptr<LAMatrix>& A, const std::shared_ptr<LAVector>& b);
	void solve( LAVector& sol );
	void apply_preconditioner(LAVector* rPrev, LAVector* rPrevHat) const;
private:
	std::shared_ptr<ControlParameters> control_;
	std::shared_ptr<LAMatrix> A_;
	std::shared_ptr<LAVector> b_;
	unsigned int maxIterations_;
	mutable LAVector r_prev, rhat_prev, r_curr, rhat_curr;
	mutable LAVector z_prev, zhat_prev, sol_prev, q_curr, qhat_curr;
	mutable LAVector p_curr, phat_curr, p_prev, phat_prev;
	mutable double alpha_curr, rho_prev, rho_prev2, beta_prev;
	bool usePreconditioner_;
};

#endif