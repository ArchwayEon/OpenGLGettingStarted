#pragma once
#include <glad/glad.h>
#include <vector>
#include "VertexBuffer.h"
class Mesh
{
protected:
	int m_numberOfVertices;
	std::vector<float> m_vertexData;

public:
	VertexBuffer vertexBuffer;

public:
	virtual ~Mesh() = default;
	void SetNumberOfVertices(int numberOfVertices) { m_numberOfVertices = numberOfVertices; }
	void AddVertexData(int count, ...);
	void Render(unsigned int shaderProgramId);
	void CreateBuffers();
};

