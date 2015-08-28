#include <SparseMatrix.h>

#include <algorithm>

SparseMatrix::SparseMatrix( size_t numRows, size_t numCols, size_t numNonZeroEntries )
	:numRows_(numRows), numCols_(numCols), 
	rowPtr_(std::vector<unsigned int>(numRows)), 
	val_(std::vector<double>(numNonZeroEntries)), 
	colInd_(std::vector<unsigned int>(colInd_)),
	zero_(0.0)
{};

SparseMatrix::SparseMatrix( const std::vector<double>& val, const std::vector<unsigned int>& colInd, 
	const std::vector<unsigned int>& rowPtr, size_t numRows, size_t numCols )
	: val_(val), colInd_(colInd), rowPtr_(rowPtr),
	numRows_(numRows), numCols_(numCols),
	zero_(0.0)
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

	//search for row for location on colum -->edit
	//auto begin = std::find(rowPtr_.begin(), rowPtr_.end(),i);

	//search column for val location
	unsigned int startIndex = rowPtr_[i];
	unsigned int endIndex = rowPtr_[i+1];

	auto startIndexIter = colInd_.begin() + startIndex;
	auto endIndexIter = colInd_.begin() + endIndex;
	auto locVal = std::find(startIndexIter,endIndexIter,j);
	unsigned int loc = std::distance(colInd_.begin(),locVal);

	if( locVal == endIndexIter )
		return zero_;
	else
		return val_[loc];
};

//double& SparseMatrix:: operator() (unsigned int i, unsigned int j ) 
//{
//	return const_cast<double&>( static_cast<const SparseMatrix&> (*this)(i,j) );
//};

void SparseMatrix::vec_multiply(LAVector& in, LAVector& out) const
{
	if( in.size() != out.size() )
		return; //throw;

	if( numCols_ != in.size() )
		return; //throw;

	for( unsigned int rowCtr = 0; rowCtr < numRows_; ++rowCtr )
	{
		double result = 0.0;

		//get range of elements of each row
		unsigned int startIndex = rowPtr_[rowCtr];
		unsigned int endIndex = rowPtr_[rowCtr+1];

		for( unsigned int colCtr = startIndex; colCtr < endIndex; ++colCtr)
		{
			result += val_[colCtr]*in(colInd_[colCtr]);
		};

		out(rowCtr) = result;
	};

};