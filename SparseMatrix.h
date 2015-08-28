#ifndef SPARSEMATRIX_H_
#define SPARSEMATRIX_H_

#include <vector>
#include <LAContainers.h>

class SparseMatrix
{
public:
	SparseMatrix( size_t numRows, size_t numCols, size_t numNonZeroEntries );
	SparseMatrix( const std::vector<double>& val, const std::vector<unsigned int>& colInd, 
		const std::vector<unsigned int>& rowPtr, size_t numRows, size_t numCols );

	SparseMatrix& operator += ( double a );
	SparseMatrix& operator *= ( double a );
	SparseMatrix& operator -= ( double a );
	SparseMatrix& operator /= ( double a );

	const double& operator() (unsigned int i, unsigned int j ) const;
	void vec_multiply(LAVector& in, LAVector& out) const;

private:
	std::vector<double> val_; 
	std::vector<unsigned int> colInd_, rowPtr_;
	size_t numRows_, numCols_;
	const double zero_; 
};

#endif