#ifndef FEM_H_
#define FEM_H_

#include <FiniteElement.h>
#include <QuadrilateralFE.h>
#include <Quadrature.h>
#include <QuadratureGenerator.h>
#include <CartesianMapping.h>
#include <FECalculationEngine.h>

#define NAME "FEM"

#if defined(_DEBUG)
#	define TYPE "-d"
#else
#   define TYPE "-r"
#endif

#define LIB_NAME NAME TYPE ".lib"

#pragma comment(lib, LIB_NAME)

#endif