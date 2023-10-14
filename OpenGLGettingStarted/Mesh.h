#pragma once
#include <glad/glad.h>
#include <vector>
#include "ReferenceFrame.h"
#include "GraphicsStructures.h"
#include "VertexBuffer.h"

class Mesh
{
protected:
	int m_numberOfVertices;
	std::vector<float> m_vertexData;
	int m_numberOfIndices;
	std::vector<unsigned short int> m_indexData;
	std::shared_ptr<VertexBuffer> m_buffer;

public:
	ReferenceFrame frame;
	Material material;

public:
	Mesh();
	virtual ~Mesh() = default;
	void SetNumberOfVertices(int numberOfVertices) { m_numberOfVertices = numberOfVertices; }
	void SetNumberOfIndices(int numberOfIndices) { m_numberOfIndices = numberOfIndices; }
	void AddVertexData(int count, ...);
	void AddVertex(Position pos, RGB color);
	void AddVertex(Position pos, RGB color, Direction normal);
	void AddIndexData(int count, ...);
	void AddTriangle(Position pos1, Position pos2, Position pos3, RGB color);
	void AddTriangleIndices(unsigned short int idx1, unsigned short int idx2, unsigned short int idx3);
	const std::vector<float>& GetVertexData() const { return m_vertexData; }
	const std::vector<unsigned short int>& GetIndexData() const { return m_indexData; }
	void SetBuffer(const std::shared_ptr<VertexBuffer>& buffer) { m_buffer = buffer; }
	const std::shared_ptr<VertexBuffer>& GetBuffer() { return m_buffer; }
};

