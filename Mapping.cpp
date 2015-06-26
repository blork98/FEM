#include<Mapping.h>

Mapping::Mapping(const unsigned int& dim)
	:dim_(dim)
{};

const unsigned int& Mapping::dim() const
{
	return dim_;	
};