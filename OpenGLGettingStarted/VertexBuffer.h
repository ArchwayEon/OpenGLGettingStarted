#pragma once
#include <vector>
#include <memory>
#include "GraphicsStructures.h"
#include "GraphicsObject.h"

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
	unsigned int m_iboId;
	bool m_isIndexed;
	int m_primitiveType;
	std::size_t m_vertexCount;
	std::size_t m_indexCount;

public:
	std::shared_ptr<GraphicsObject> attachedObject;

public:
	VertexBuffer();
	~VertexBuffer();
	unsigned int GetVBOId() const { return m_vboId; }
	const std::vector<VertexAttribute>& GetAttributes() { return m_attributes; }
	void SetIsIndexed(bool isIndexed) { m_isIndexed = isIndexed; }
	bool IsIndexed() const { return m_isIndexed; }
	void SetPrimitiveType(int primitiveType) { m_primitiveType = primitiveType; }
	int GetPrimitiveType() const { return m_primitiveType; }
	std::size_t GetVertexCount() const { return m_vertexCount; }
	void SetVertexCount(std::size_t vertexCount) { m_vertexCount = vertexCount; }
	void GenerateIndexedBuffer();
	unsigned int GetIBOId() const { return m_iboId; }
	std::size_t GetIndexCount() const { return m_indexCount; }
	void SetIndexCount(std::size_t indexCount) { m_indexCount = indexCount; }

	void Select() const;
	void Unselect() const;
	void AddVertexAttribute(const VertexAttribute& attr);
	void EnableAttributes() const;
	void StaticAllocate(std::vector<float> vertexData);
	void StaticAllocate(const std::vector<unsigned short int>& indexData);
	void DisableAttributes() const;
};

