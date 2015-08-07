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
	CGSolver( unsigned int maxIterations, std::shared_ptr<ControlParameters>& control);
	void solve( LAVector& sol );
private:
	std::shared_ptr<ControlParameters> control_;
	unsigned int maxIterations_;
};

#endif