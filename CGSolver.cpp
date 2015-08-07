#include <CGSolver.h>

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

CGSolver::CGSolver( unsigned int maxIterations, std::shared_ptr<ControlParameters>& control)
	:maxIterations_(maxIterations), control_(control)
{};

void CGSolver::solve( LAVector& sol )
{

};