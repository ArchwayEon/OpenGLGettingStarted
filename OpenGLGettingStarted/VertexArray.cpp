#include "VertexArray.h"
#include <glad/glad.h>

VertexArray::VertexArray() : m_vaoId(0)
{
	glGenVertexArrays(1, &m_vaoId);
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &m_vaoId);
}

void VertexArray::Select() const
{
	glBindVertexArray(m_vaoId);
}

void VertexArray::Unselect() const
{
	glBindVertexArray(0);
}

//void VertexArray::AddBuffer(const VertexBuffer& vb, const IndexBuffer& ib, const VertexAttribute& attr)
//{
//	m_vertexBuffers.push_back(vb);
//	m_indexBuffers.push_back(ib);
//	m_attributes.push_back(attr);
//}

//void VertexArray::EnableAttributes() const
//{
//
//}
