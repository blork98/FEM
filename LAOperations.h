#ifndef LAOPERATIONS_H_
#define LAOPERATIONS_H_

#include<LAContainers.h>

double vector_dot_product( const LAVector& vec1, const LAVector& vec2 );

LAVector operator*(const LAMatrix& mat, const LAVector& vec);
LAVector operator*( double const, const LAVector& vec);
LAVector operator+( const LAVector& vec1,  const LAVector& vec2);
LAVector operator-( const LAVector& vec1,  const LAVector& vec2);
double operator*(const LAVector& vec1,  const LAVector& vec2);

void mat_vector_product(const LAMatrix& mat, const LAVector& vec, LAVector& result);
void vector_add(const LAVector& vec1, const LAVector& vec2, LAVector& result);
void vector_subtract(const LAVector& vec1, const LAVector& vec2, LAVector& result);
void vector_scalar_mult(double scalar, const LAVector& vec1, LAVector& res);

#endif