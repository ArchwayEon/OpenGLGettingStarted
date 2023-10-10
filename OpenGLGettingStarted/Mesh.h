#pragma once
#include <glad/glad.h>
#include <vector>
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ReferenceFrame.h"

class Mesh
{
protected:
	int m_numberOfVertices;
	std::vector<float> m_vertexData;
	int m_numberOfIndices;
	std::vector<unsigned short int> m_indexData;

public:
	std::unique_ptr<VertexBuffer> vertexBuffer;
	std::unique_ptr<IndexBuffer> indexBuffer;
	ReferenceFrame frame;

public:
	Mesh() : m_numberOfVertices(0), m_numberOfIndices(0) {}
	virtual ~Mesh() = default;
	void SetNumberOfVertices(int numberOfVertices) { m_numberOfVertices = numberOfVertices; }
	void SetNumberOfIndices(int numberOfIndices) { m_numberOfIndices = numberOfIndices; }
	void AddVertexData(int count, ...);
	void AddVertex(Position pos, RGB color);
	void AddVertexAttribute(const VertexAttribute& attr);
	void AddIndexData(int count, ...);
	void AddTriangleIndices(unsigned short int idx1, unsigned short int idx2, unsigned short int idx3);
	void Render() const;
	void AllocateStaticBuffers();
};

