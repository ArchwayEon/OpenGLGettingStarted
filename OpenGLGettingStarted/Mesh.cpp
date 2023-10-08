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

void Mesh::AddIndexData(int count, ...)
{
	va_list args;
	va_start(args, count);

	while (count > 0) {
		m_indexData.push_back(static_cast<unsigned short int>(va_arg(args, int)));
		count--;
	}

	va_end(args);
}

void Mesh::Render(unsigned int shaderProgramId)
{
	vertexBuffer.EnableAttributes();
	glDrawElements(GL_TRIANGLES, m_numberOfIndices, GL_UNSIGNED_SHORT, 0);
	vertexBuffer.DisableAttributes();
}

void Mesh::CreateBuffers()
{
	vertexBuffer.Generate();
	vertexBuffer.StaticAllocateVertices(m_vertexData);
	vertexBuffer.StaticAllocateIndices(m_indexData);
}
