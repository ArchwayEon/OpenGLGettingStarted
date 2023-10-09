#pragma once
#include <vector>
#include <memory>
#include "GraphicsStructures.h"
#include "VertexArray.h"

struct VertexAttribute {
	unsigned int index;
	int numberOfComponents;
	int type;
	int isNormalized;
	unsigned int bytesToNext;
	void* byteOffset;
};

class VertexBuffer
{
protected:
	std::vector<VertexAttribute> m_attributes;
	unsigned int m_vboId;
	//unsigned int m_iboId;

public:
	std::shared_ptr<VertexArray> vertexArray;

public:
	//VertexBuffer() : m_attributes{}, m_vboId(0), m_iboId() {}
	VertexBuffer();
	~VertexBuffer();
	void Select() const;
	void Unselect() const;
	void AddVertexAttribute(const VertexAttribute& attr);
	void EnableAttributes() const;
	void StaticAllocate(std::vector<float> vertexData);
	void DisableAttributes() const;
};

