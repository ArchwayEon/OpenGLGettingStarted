#include <cstdarg>
#include "Mesh.h"

void Mesh::AddVertexData(int count, ...)
{
	va_list args;
	va_start(args, count);

	while (count > 0) {
		// The default is double, so accept as double and then cast to
		// float.
		m_vertexData.push_back(static_cast<float>(va_arg(args, double)));
		count--;
	}

	va_end(args);
}

void Mesh::AddVertexAttribute(const VertexAttribute& attr)
{
	vertexBuffer->AddVertexAttribute(attr);
}

void Mesh::AddIndexData(int count, ...)
{
	va_list args;
	va_start(args, count);
	m_numberOfIndices += count;
	while (count > 0) {
		m_indexData.push_back(static_cast<unsigned short int>(va_arg(args, int)));
		count--;
	}
	va_end(args);
}

void Mesh::AddTriangleIndices(unsigned short int idx1, unsigned short int idx2, unsigned short int idx3)
{
	m_indexData.push_back(idx1);
	m_indexData.push_back(idx2);
	m_indexData.push_back(idx3);
	m_numberOfIndices += 3;
}

void Mesh::Render() const
{
	vertexBuffer->EnableAttributes();
	indexBuffer->Select();
	glDrawElements(GL_TRIANGLES, m_numberOfIndices, GL_UNSIGNED_SHORT, 0);
	vertexBuffer->DisableAttributes();
}

void Mesh::AllocateStaticBuffers()
{
	vertexBuffer->StaticAllocate(m_vertexData);
	indexBuffer->StaticAllocate(m_indexData);
}
