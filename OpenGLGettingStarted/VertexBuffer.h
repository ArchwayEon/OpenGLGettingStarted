#pragma once
#include <vector>
#include <unordered_map>
#include <memory>
#include <string>
#include "GraphicsStructures.h"
//#include "GraphicsObject.h"

struct VertexAttribute {
	unsigned int index;
	unsigned int numberOfComponents;
	int type;
	int isNormalized;
	unsigned int bytesToNext;
	void* byteOffset;
};

enum BufferDataType {VertexData, IndexData};

class VertexBuffer
{
protected:
	std::unordered_map<std::string, VertexAttribute> m_attributeMap;
	std::unordered_map<std::string, unsigned int> m_bufferIdMap;
	std::unordered_map<std::string, BufferDataType> m_bufferTypeMap;
	unsigned int m_vboId;
	unsigned int m_iboId;
	bool m_isIndexed;
	int m_primitiveType;
	std::size_t m_vertexCount;
	std::size_t m_indexCount;
	unsigned int m_numberOfElementsPerVertex;

public:
	VertexBuffer(unsigned int numberOfElementsPerVertex = 9);
	~VertexBuffer();
	void GenerateBufferId(const std::string& bufferName, BufferDataType type);
	unsigned int GetBufferId(const std::string& bufferName) { return m_bufferIdMap[bufferName]; }
	const std::unordered_map<std::string, VertexAttribute>& GetAttributeMap() { return m_attributeMap; }
	void SetIsIndexed(bool isIndexed) { m_isIndexed = isIndexed; }
	bool IsIndexed() const { return m_isIndexed; }
	void SetPrimitiveType(int primitiveType) { m_primitiveType = primitiveType; }
	int GetPrimitiveType() const { return m_primitiveType; }
	std::size_t GetVertexCount() const { return m_vertexCount; }
	void SetVertexCount(std::size_t vertexCount) { m_vertexCount = vertexCount; }
	std::size_t GetIndexCount() const { return m_indexCount; }
	void SetIndexCount(std::size_t indexCount) { m_indexCount = indexCount; }
	void SetNumberOfElementsPerVertex(unsigned int numberOfElementsPerVertex) {
		m_numberOfElementsPerVertex = numberOfElementsPerVertex;
	}
	std::size_t GetVertexSizeInBytes() const {
		return sizeof(float) * m_numberOfElementsPerVertex;
	}
	std::size_t GetOffsetInBytes(unsigned int index) const {
		return sizeof(float) * index;
	}

	void Select(const std::string& bufferName);
	void Unselect() const;
	void AddVertexAttribute(const std::string& name, unsigned int index, unsigned int numberOfElements);
	void AddVertexAttribute(const std::string& name, const VertexAttribute& attr);
	void StaticAllocate(const std::string& bufferName, std::vector<float> vertexData);
	void StaticAllocate(const std::string& bufferName, const std::vector<unsigned short int>& indexData);
	void DisableAttributes() const;
};

