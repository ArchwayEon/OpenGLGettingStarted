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

