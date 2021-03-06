#include <LAContainers.h>

#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/matrix.hpp>

/////////////////////////////////////////////// Base Vec Impl Class //////////////////////////////////////

class VecImpl
{
public:
    double& operator() ( unsigned int i);
    virtual const double& operator() ( unsigned int i) const = 0;
};

double& VecImpl::operator () ( unsigned int i )
{
    return const_cast<double&>( static_cast<const VecImpl&> (*this)(i) );
};

///////////////////////////////////////////// Derived Classes 

class STDVector : public VecImpl
{
public:
    STDVector( size_t size);
    STDVector( size_t size, double vals);
    STDVector( const std::vector<double>& vec);
    
    virtual const double& operator() ( unsigned int i) const;
private:
    std::vector<double> data_;
};

STDVector::STDVector( size_t size)
	: data_(size,0.0)
{};

STDVector::STDVector(size_t size, double vals)
	: data_(size,vals)
{};

STDVector::STDVector( const std::vector<double>& vec)
	: data_(vec)
{};

const double& STDVector::operator() ( unsigned int i) const
{
	return data_[i];
};

class UBLASVector : public VecImpl
{
public:
	UBLASVector( size_t size);
    UBLASVector( size_t size, double vals);
    UBLASVector( const std::vector<double>& vec);

	virtual const double& operator() ( unsigned int i) const;

private:
	boost::numeric::ublas::vector<double> data_;
};

UBLASVector::UBLASVector( size_t size)
	: data_(size,0.0)
{};

UBLASVector::UBLASVector(size_t size, double vals)
	: data_(size,vals)
{};

UBLASVector::UBLASVector( const std::vector<double>& vec)
{
	for( unsigned int i = 0; i < vec.size(); ++i )
		data_(i) = vec[i];
};

const double& UBLASVector::operator() ( unsigned int i) const
{
	return data_(i);
};

//////////////////////////////// LAVector class

LAVector::LAVector()
	:vecImpl( std::unique_ptr<VecImpl>() ), size_(0)
{};

LAVector::LAVector( const LAVector& vec)
	:size_(vec.size()), contType(vec.container_type())
{
	switch(contType)
	{
		case STDVEC:
			vecImpl = std::unique_ptr<VecImpl>(new STDVector(size_));
			break;
		case BOOSTUBLAS:
			vecImpl = std::unique_ptr<VecImpl>(new UBLASVector(size_));
			break;
		default:
			vecImpl = std::unique_ptr<VecImpl>(new STDVector(size_));
			break;
	};

	for( size_t i = 0; i < size_; ++i )
		(*vecImpl)(i) = vec(i);
};

LAVector::LAVector( LAVector::ContainerType type, size_t size)
	:size_(size), contType(type)
{
	switch(type)
	{
		case STDVEC:
			vecImpl = std::unique_ptr<VecImpl>(new STDVector(size));
			break;
		case BOOSTUBLAS:
			vecImpl = std::unique_ptr<VecImpl>(new UBLASVector(size));
			break;
		default:
			vecImpl = std::unique_ptr<VecImpl>(new STDVector(size));
			break;
	};
};

LAVector::LAVector( LAVector::ContainerType type, size_t size, double vals)
	:size_(size), contType(type)
{
	switch(type)
	{
		case STDVEC:
			vecImpl = std::unique_ptr<VecImpl>(new STDVector(size,vals));
			break;
		case BOOSTUBLAS:
			vecImpl = std::unique_ptr<VecImpl>(new UBLASVector(size,vals));
			break;
		default:
			vecImpl = std::unique_ptr<VecImpl>(new STDVector(size,vals));
			break;
	};
};

LAVector::LAVector( LAVector::ContainerType type, const std::vector<double>& vec)
	:size_(vec.size()), contType(type)
{
	switch(type)
	{
		case STDVEC:
			vecImpl = std::unique_ptr<VecImpl>(new STDVector(vec));
			break;
		case BOOSTUBLAS:
			vecImpl = std::unique_ptr<VecImpl>(new UBLASVector(vec));
			break;
		default:
			vecImpl = std::unique_ptr<VecImpl>(new STDVector(vec));
			break;
	};
};

LAVector::~LAVector()
{};

LAVector::ContainerType LAVector::container_type() const
{
	return contType;
};

size_t LAVector::size() const
{
	return size_;
};

LAVector&  LAVector::operator= (const LAVector& rhs)
{
	if( this != &rhs ) 
	{
		if( this->size() != rhs.size() )
		{
			size_ = rhs.size();
			vecImpl.reset();

			switch(contType)
			{
				case STDVEC:
					vecImpl = std::unique_ptr<VecImpl>(new STDVector(size_));
					break;
				case BOOSTUBLAS:
					vecImpl = std::unique_ptr<VecImpl>(new UBLASVector(size_));
					break;
				default:
					vecImpl = std::unique_ptr<VecImpl>(new STDVector(size_));
					break;
			};
		};

		for( size_t i = 0; i < rhs.size(); ++i )
			(*vecImpl)(i) = rhs(i);

	};

	return (*this);
};

double& LAVector::operator() ( unsigned int i)
{
	return (*vecImpl)(i);
};

const double& LAVector::operator() ( unsigned int i) const
{
	return (*vecImpl)(i);
};

///////////////////////////////////////////// Base Matrix Class Impl ///////////////////////////////

class MatImpl
{
public:
    double& operator() ( unsigned int i, unsigned int j);
    virtual const double& operator() ( unsigned int i, unsigned int j) const = 0;
};

double& MatImpl::operator () ( unsigned int i, unsigned int j )
{
    return const_cast<double&>( static_cast<const MatImpl&> (*this)(i,j) );
};

//////////////////////////////////////// Derived Matrix Implementations

class STDMatrix : public MatImpl
{
public:
	STDMatrix( size_t numRows, size_t numCols);
    STDMatrix( size_t numRows, size_t numCols,double vals);
    STDMatrix( const std::vector<std::vector<double>>& mat);

	virtual const double& operator() ( unsigned int i, unsigned int j) const;

private:
	std::vector<std::vector<double>> data_;
};

STDMatrix::STDMatrix( size_t numRows, size_t numCols)
	: data_(numRows, std::vector<double>(numCols,0.0))
{};

STDMatrix::STDMatrix(size_t numRows, size_t numCols, double val)
	:data_(numRows, std::vector<double>(numCols,val))
{};

STDMatrix::STDMatrix( const std::vector<std::vector<double>>& mat)
	:data_(mat)
{};

const double& STDMatrix::operator() (unsigned int i, unsigned int j) const
{
	return data_[i][j];
};

class UBLASMatrix : public MatImpl
{
public:
	UBLASMatrix( size_t numRows, size_t numcols);
	UBLASMatrix( size_t numRows, size_t numCols, double val);
	UBLASMatrix( const std::vector<std::vector<double>>& mat);

	virtual const double& operator() ( unsigned int i, unsigned int j) const;

private:
	boost::numeric::ublas::matrix<double> data_;
};

UBLASMatrix::UBLASMatrix( size_t numRows, size_t numcols)
	: data_(numRows, numcols, 0.0)
{};

UBLASMatrix::UBLASMatrix( size_t numRows, size_t numCols, double val)
	: data_(numRows, numCols, 0.0)
{};

UBLASMatrix::UBLASMatrix( const std::vector<std::vector<double>>& mat)
	: data_(mat.size(), mat[0].size(), 0.0)
{
	for( unsigned int i = 0; i < mat.size(); ++i )
	{
		for( unsigned int j = 0; j < mat.size(); ++j )
			data_(i,j) = mat[i][j];
	};
};

const double& UBLASMatrix::operator() (unsigned int i, unsigned int j) const
{
	return data_(i,j);
};

//////////////////////////////////////LA Matrix

LAMatrix::LAMatrix()
	:matImpl(std::unique_ptr<MatImpl>()), contType(LAMatrix::STDMAT),
	numCols_(0), numRows_(0)
{};

LAMatrix::LAMatrix( const LAMatrix& mat)
	:contType(mat.container_type() ), numRows_(mat.num_rows()), numCols_(mat.num_cols())
{
	switch(contType)
	{
		case STDMAT:
			matImpl = std::unique_ptr<MatImpl>(new STDMatrix(numRows_,numCols_));
			break;
		case BOOSTUBLAS:
			matImpl = std::unique_ptr<MatImpl>(new UBLASMatrix(numRows_,numCols_));
			break;
		default:
			matImpl = std::unique_ptr<MatImpl>(new STDMatrix(numRows_,numCols_));
			break;
	};

	for( unsigned int i = 0; i < numRows_; ++i )
		for( unsigned int j = 0; j < numCols_; ++j)
			(*matImpl)(i,j) = mat(i,j);
};

LAMatrix::LAMatrix( LAMatrix::ContainerType type, size_t numRows, size_t numCols)
	:numRows_(numRows), numCols_(numCols), contType(type)
{
	switch(type)
	{
		case STDMAT:
			matImpl = std::unique_ptr<MatImpl>(new STDMatrix(numRows,numCols));
			break;
		case BOOSTUBLAS:
			matImpl = std::unique_ptr<MatImpl>(new UBLASMatrix(numRows,numCols));
			break;
		default:
			matImpl = std::unique_ptr<MatImpl>(new STDMatrix(numRows,numCols));
			break;
	};
};

LAMatrix::LAMatrix(LAMatrix::ContainerType type, size_t numRows, size_t numCols, double vals)
	:numRows_(numRows), numCols_(numCols), contType(type)
{
	switch(type)
	{
		case STDMAT:
			matImpl = std::unique_ptr<MatImpl>(new STDMatrix(numRows,numCols,vals));
			break;
		case BOOSTUBLAS:
			matImpl = std::unique_ptr<MatImpl>(new UBLASMatrix(numRows,numCols,vals));
			break;
		default:
			matImpl = std::unique_ptr<MatImpl>(new STDMatrix(numRows,numCols,vals));
			break;
	};
};

LAMatrix::LAMatrix(LAMatrix::ContainerType type, const std::vector<std::vector<double>>& mat)
	: contType(type), numRows_(mat.size()), numCols_(mat[0].size())
{
	switch(type)
	{
		case STDMAT:
			matImpl = std::unique_ptr<MatImpl>(new STDMatrix(mat));
			break;
		case BOOSTUBLAS:
			matImpl = std::unique_ptr<MatImpl>(new UBLASMatrix(mat));
			break;
		default:
			matImpl = std::unique_ptr<MatImpl>(new STDMatrix(mat));
			break;
	};
};

LAMatrix::~LAMatrix()
{};

double& LAMatrix::operator() ( unsigned int i, unsigned int j)
{
	return (*matImpl)(i,j);
};

const double& LAMatrix::operator() ( unsigned int i, unsigned int j) const
{
	return (*matImpl)(i,j);
};

size_t LAMatrix::num_rows() const
{
	return numRows_;
};

size_t LAMatrix::num_cols() const
{
	return numCols_;
};

LAMatrix::ContainerType LAMatrix::container_type() const
{
	return contType;
};