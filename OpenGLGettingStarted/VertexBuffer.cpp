#include "VertexBuffer.h"

void VertexBuffer::AddVertexAttribute(unsigned int index, int numberOfComponents, int type, int isNormalized, unsigned int bytesToNext, int offset)
{
	VertexAttribute attr;
	attr.index = index;
	attr.numberOfComponents = numberOfComponents;
	m_attributes.push_back(attr);
}
