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

void Mesh::AddVertex(Position pos, RGB color)
{
	m_vertexData.push_back(pos.x);
	m_vertexData.push_back(pos.y);
	m_vertexData.push_back(pos.z);
	m_vertexData.push_back(color.red);
	m_vertexData.push_back(color.green);
	m_vertexData.push_back(color.blue);
	m_numberOfVertices++;
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

void Mesh::AddTriangle(Position pos1, Position pos2, Position pos3, RGB color)
{
	AddVertex(pos1, color);
	AddVertex(pos2, color);
	AddVertex(pos3, color);
}

void Mesh::AddTriangleIndices(unsigned short int idx1, unsigned short int idx2, unsigned short int idx3)
{
	m_indexData.push_back(idx1);
	m_indexData.push_back(idx2);
	m_indexData.push_back(idx3);
	m_numberOfIndices += 3;
}

