#pragma once
#include <vector>
#include <memory>
#include "GraphicsStructures.h"

class VertexBuffer
{
	struct VertexAttribute {
		unsigned int index; // index of the generic vertex attribute to be modified
		int numberOfComponents; // number of components per generic vertex attribute: 1, 2, 3, or 4
		int type; // the data type of each component in the array
		int isNormalized; // specifies whether fixed-point data values should be normalized or converted directly as fixed-point values
		unsigned int bytesToNext; // Specifies the byte offset between consecutive generic vertex attributes
		void* byteOffset; // Specifies a offset of the first component of the first generic vertex attribute in the array
	};
protected:
	std::vector<VertexAttribute> m_attributes;
	unsigned int m_vboId;
	unsigned int m_iboId;

public:
	VertexBuffer() : m_attributes{}, m_vboId(0), m_iboId() {}
	void Generate();
	void AddVertexAttribute(
		unsigned int index, int numberOfComponents, int type, int isNormalized, unsigned int bytesToNext, unsigned long long offset);
	void EnableAttributes();
	void StaticAllocateVertices(std::vector<float> vertexData);
	void StaticAllocateIndices(std::vector<unsigned short int> indexData);
	void DisableAttributes();
};

