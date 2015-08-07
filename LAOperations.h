#ifndef LAOPERATIONS_H_
#define LAOPERATIONS_H_

#include<LAContainers.h>

double vector_dot_product( const LAVector& vec1, const LAVector& vec2 );

LAVector operator*(const LAMatrix& mat, const LAVector& vec);

#endif