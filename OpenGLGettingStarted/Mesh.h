#pragma once
#include <glad/glad.h>
#include <vector>
#include "ReferenceFrame.h"
#include "GraphicsStructures.h"

class Mesh
{
protected:
	int m_numberOfVertices;
	std::vector<float> m_vertexData;
	int m_numberOfIndices;
	std::vector<unsigned short int> m_indexData;

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
};

