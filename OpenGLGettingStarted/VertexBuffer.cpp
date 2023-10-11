#include "VertexBuffer.h"
#include <glad/glad.h>

VertexBuffer::VertexBuffer() : 
	m_vboId(0), m_iboId(0), m_isIndexed(false), m_primitiveType(GL_TRIANGLES), 
	m_vertexCount(0), m_indexCount(0)
{
	glGenBuffers(1, &m_vboId);
}

VertexBuffer::~VertexBuffer()
{
}

void VertexBuffer::GenerateIndexedBuffer()
{
	glGenBuffers(1, &m_iboId);
	m_isIndexed = true;
}

void VertexBuffer::Select() const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_vboId);
}

void VertexBuffer::Unselect() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::AddVertexAttribute(const VertexAttribute& attr)
{
	m_attributes.push_back(attr);
}

void VertexBuffer::EnableAttributes() const
{
	//vertexArray->Select();
	//Select();
	//for (unsigned int i = 0; i < m_attributes.size(); i++) {
	//	const auto& attr = m_attributes[i];
	//	glEnableVertexAttribArray(attr.index);
	//	glVertexAttribPointer(
	//		attr.index, attr.numberOfComponents, attr.type,
	//		attr.isNormalized, attr.bytesToNext, attr.byteOffset
	//	);
	//}
}

void VertexBuffer::StaticAllocate(std::vector<float> vertexData)
{
	m_vertexCount = vertexData.size();
	unsigned long long bytesToAllocate = vertexData.size() * sizeof(float);
	glBindBuffer(GL_ARRAY_BUFFER, m_vboId);
	glBufferData(GL_ARRAY_BUFFER, bytesToAllocate, vertexData.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::DisableAttributes() const
{
	for (unsigned int i = 0; i < m_attributes.size(); i++) {
		const auto& attr = m_attributes[i];
		glDisableVertexAttribArray(attr.index);
	}
}

void VertexBuffer::StaticAllocate(const std::vector<unsigned short int>& indexData)
{
	m_indexCount = indexData.size();
	unsigned long long bytesToAllocate = indexData.size() * sizeof(unsigned short int);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_iboId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, bytesToAllocate, indexData.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
