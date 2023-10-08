#pragma once
#include <glad/glad.h>
#include <vector>
#include "VertexBuffer.h"
class Mesh
{
protected:
	int m_numberOfVertices;
	std::vector<float> m_vertexData;
	int m_numberOfIndices;
	std::vector<unsigned short int> m_indexData;

public:
	VertexBuffer vertexBuffer;

public:
	Mesh() : m_numberOfVertices(0), m_numberOfIndices(0) {}
	virtual ~Mesh() = default;
	void SetNumberOfVertices(int numberOfVertices) { m_numberOfVertices = numberOfVertices; }
	void SetNumberOfIndices(int numberOfIndices) { m_numberOfIndices = numberOfIndices; }
	void AddVertexData(int count, ...);
	void AddIndexData(int count, ...);
	void Render(unsigned int shaderProgramId);
	void CreateBuffers();
};

