#include <SparseMatrix.h>

#include <algorithm>

SparseMatrix::SparseMatrix( size_t numRows, size_t numCols, size_t numNonZeroEntries )
	:numRows_(numRows), numCols_(numCols), 
	rowPtr_(std::vector<unsigned int>(numRows)), 
	val_(std::vector<double>(numNonZeroEntries)), 
	colInd_(std::vector<unsigned int>(colInd_))
{};

SparseMatrix::SparseMatrix( const std::vector<double>& val, const std::vector<unsigned int>& colInd, 
	const std::vector<unsigned int>& rowPtr, size_t numRows, size_t numCols )
	: val_(val), colInd_(colInd), rowPtr_(rowPtr),
	numRows_(numRows), numCols_(numCols)
{};

SparseMatrix& SparseMatrix::operator += ( double a )
{
	for ( unsigned int i = 0; i < val_.size(); ++i )
		val_[i] += a;

	return *this;
};

SparseMatrix& SparseMatrix::operator *= ( double a )
{
	for ( unsigned int i = 0; i < val_.size(); ++i )
		val_[i] *= a;

	return *this;
};

SparseMatrix& SparseMatrix::operator -= ( double a )
{
	for ( unsigned int i = 0; i < val_.size(); ++i )
		val_[i] -= a;

	return *this;
};

SparseMatrix& SparseMatrix::operator /= ( double a )
{
	for ( unsigned int i = 0; i < val_.size(); ++i )
		val_[i] /= a;

	return *this;
};

const double& SparseMatrix::operator() (unsigned int i, unsigned int j ) const
{
	//if out of bounds
	if( i > numRows_ || j > numCols_ )
		throw;

	//search for row for location on colum
	auto begin = std::find(rowPtr_.begin(), rowPtr_.end(),i);

	//search column for val location
	unsigned int startIndex = *begin;
	unsigned int endIndex = *(begin + 1 );
	auto startIndexIter = colInd_.begin() + startIndex;
	auto endIndexIter = colInd_.begin() + endIndex;
	auto locVal = std::find(startIndexIter,endIndexIter,j);

	if( locVal == endIndexIter )
		return 0.0;
	else
		return val_[*locVal];
};

double& SparseMatrix:: operator() (unsigned int i, unsigned int j ) 
{
	return const_cast<double&>( static_cast<const SparseMatrix&> (*this)(i,j) );
};