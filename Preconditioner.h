#ifndef PRECONDITIONER_H_
#define PRECONDITIONER_H_

#include <LASolver.h>

class Preconditioner
{
public:
	Preconditioner(const std::shared_ptr<LAVector>& b, const std::shared_ptr<LAMatrix>& A,
		const std::shared_ptr<LinearSolver>& solver);
	virtual void solve( LAVector& sol);

protected:
	virtual void create_precondioner(const std::shared_ptr<LAMatrix>& A) = 0;

	std::shared_ptr<LAMatrix> M_;
	std::shared_ptr<LAVector> b_;
	std::shared_ptr<LinearSolver> solver_;
};

class JacobiPC : public Preconditioner
{
public:
	JacobiPC(const std::shared_ptr<LAVector>& b, const std::shared_ptr<LAMatrix>& A,
		const std::shared_ptr<LinearSolver>& solver);
	virtual void solve( LAVector& sol);

protected:
	virtual void create_precondioner(const std::shared_ptr<LAMatrix>& A);
};

#endif
