#include <LAOperations.h>

double vector_dot_product( const LAVector& vec1, const LAVector& vec2 )
{
	double result = 0.0;

	if( vec1.size() != vec2.size() )
		throw;

	for( size_t i = 0; i < vec1.size(); ++i )
		result += vec1(i)*vec2(i);

	return result;
};

LAVector operator*(const LAMatrix& mat, const LAVector& vec)
{
	LAVector result(LAVector::STDVEC, vec.size(),0.0);

	if( vec.size() != mat.num_cols() )
		throw;

	for( size_t vecElem = 0; vecElem < vec.size(); ++vecElem )
	{
		for( size_t matCols = 0; matCols < mat.num_cols(); ++matCols )
			result(vecElem) += vec(matCols)*mat(vecElem,matCols);
	};

	return std::move(result);
};

LAVector operator*( double scalar, const LAVector& vec)
{
	LAVector result(LAVector::STDVEC, vec.size(),0.0);

	for( size_t i = 0; i < vec.size(); ++i )
	{
		result(i) = scalar*vec(i);
	};

	return result;
};

LAVector operator+( const LAVector& vec1,  const LAVector& vec2)
{
	LAVector result(LAVector::STDVEC, vec1.size(),0.0);

	if( vec1.size() != vec2.size() )
		throw;

	for( size_t i = 0; i < vec1.size(); ++i )
		result(i) = vec1(i) + vec2(i);

	return result;
};

LAVector operator-( const LAVector& vec1,  const LAVector& vec2)
{
	LAVector result(LAVector::STDVEC, vec1.size(),0.0);

	if( vec1.size() != vec2.size() )
		throw;

	for( size_t i = 0; i < vec1.size(); ++i )
		result(i) = vec1(i) - vec2(i);

	return result;
};

double operator*(const LAVector& vec1,  const LAVector& vec2)
{
	double result = 0.0;

	if( vec1.size() != vec2.size() )
		throw;

	for( size_t i = 0; i < vec1.size(); ++i )
		result += vec1(i)*vec2(i);

	return result;
};

void mat_vector_product(const LAMatrix& mat, const LAVector& vec, LAVector& result)
{
	if( vec.size() != mat.num_cols() )
		throw;

	for( size_t vecElem = 0; vecElem < vec.size(); ++vecElem )
	{
		for( size_t matCols = 0; matCols < mat.num_cols(); ++matCols )
			result(vecElem) += vec(matCols)*mat(vecElem,matCols);
	};
};

void vector_add(const LAVector& vec1, const LAVector& vec2, LAVector& result)
{
	if( vec1.size() != vec2.size() )
		throw;

	for( size_t i = 0; i < vec1.size(); ++i )
		result(i) = vec1(i) + vec2(i);
};


void vector_subtract(const LAVector& vec1, const LAVector& vec2, LAVector& result)
{
	if( vec1.size() != vec2.size() )
		throw;

	for( size_t i = 0; i < vec1.size(); ++i )
		result(i) = vec1(i) - vec2(i);
};

void vector_scalar_mult(double scalar, const LAVector& vec1, LAVector& result)
{
	if( result.size() != vec1.size() )
		throw;

	for( size_t i = 0; i < vec1.size(); ++i )
		result(i) = scalar*vec1(i);
};
