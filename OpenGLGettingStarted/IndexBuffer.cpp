#include "IndexBuffer.h"
#include <glad/glad.h>

IndexBuffer::IndexBuffer() : m_iboId(0)
{
	glGenBuffers(1, &m_iboId);
}

IndexBuffer::~IndexBuffer()
{
}

void IndexBuffer::Select() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_iboId);
}

void IndexBuffer::Unselect() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void IndexBuffer::StaticAllocate(std::vector<unsigned short int> indexData)
{
	unsigned long long bytesToAllocate = indexData.size() * sizeof(unsigned short int);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_iboId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, bytesToAllocate, indexData.data(), GL_STATIC_DRAW);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
