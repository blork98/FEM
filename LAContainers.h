#ifndef LACONTAINERS_H_
#define LACONTAINERS_H_

#include<memory>
#include<vector>

class VecImpl;
class MatImpl;

class LAVector 
{
public:
    enum ContainerType { STDVEC, BOOSTUBLAS };

	LAVector();
	LAVector( const LAVector& vec);
    LAVector( LAVector::ContainerType type, size_t size);
    LAVector( LAVector::ContainerType type, size_t size, double vals);
    LAVector( LAVector::ContainerType type, const std::vector<double>& vec);
	~LAVector();
    
	LAVector& operator= (const LAVector& rhs);
    double& operator() ( unsigned int i);
    const double& operator() ( unsigned int i) const;

	size_t size() const;
	ContainerType container_type() const;

private:
    std::unique_ptr<VecImpl> vecImpl;
	size_t size_;
	ContainerType contType;
};

class LAMatrix
{
public:
	 enum ContainerType { STDMAT, BOOSTUBLAS };

	 LAMatrix();
	 LAMatrix( LAMatrix::ContainerType type, size_t numRows, size_t numCols);
	 LAMatrix(LAMatrix::ContainerType type, size_t numRows, size_t numCols, double vals);
	 LAMatrix(LAMatrix::ContainerType type, const std::vector<std::vector<double>>& mat);
	 ~LAMatrix();

	 double& operator() ( unsigned int i, unsigned int j);
     const double& operator() ( unsigned int i, unsigned int j) const;

	 size_t num_rows() const;
	 size_t num_cols() const;

private:
	std::unique_ptr<MatImpl> matImpl;
	size_t numRows_, numCols_;
};

class SparseMatrix
{
public:

private:
};

#endif