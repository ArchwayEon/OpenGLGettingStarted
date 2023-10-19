#include "VertexBuffer.h"
#include <glad/glad.h>

VertexBuffer::VertexBuffer(unsigned int numberOfElementsPerVertex) :
	m_vboId(0), m_iboId(0), m_isIndexed(false), m_primitiveType(GL_TRIANGLES), 
	m_vertexCount(0), m_indexCount(0), m_numberOfElementsPerVertex(numberOfElementsPerVertex)
{
	
}

VertexBuffer::~VertexBuffer()
{
}

void VertexBuffer::GenerateBufferId(const std::string& bufferName, BufferDataType type)
{
	unsigned int bufferId;
	glGenBuffers(1, &bufferId);
	m_bufferIdMap[bufferName] = bufferId;
	m_bufferTypeMap[bufferName] = type;
}

void VertexBuffer::Select(const std::string& bufferName)
{
	BufferDataType type = m_bufferTypeMap[bufferName];
	switch (type) {
	case BufferDataType::VertexData:
		glBindBuffer(GL_ARRAY_BUFFER, m_bufferIdMap[bufferName]);
		break;
	case BufferDataType::IndexData:
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_bufferIdMap[bufferName]);
		break;
	}
	
}

void VertexBuffer::Unselect() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::AddVertexAttribute(const std::string& name, unsigned int index, unsigned int numberOfElements)
{
	unsigned int bytesToNext = (unsigned int)GetVertexSizeInBytes();
	unsigned long long offsetBytes = GetOffsetInBytes(index * numberOfElements);
	VertexAttribute attr = { index, numberOfElements, GL_FLOAT, GL_FALSE, bytesToNext, (void*)offsetBytes };
	m_attributeMap[name] = attr;
}

void VertexBuffer::AddVertexAttribute(const std::string& name, const VertexAttribute& attr)
{
	m_attributeMap[name] = attr;
}

void VertexBuffer::StaticAllocate(const std::string& bufferName, std::vector<float> vertexData)
{
	m_vertexCount = vertexData.size() / m_numberOfElementsPerVertex;
	unsigned long long bytesToAllocate = vertexData.size() * sizeof(float);
	Select(bufferName);
	glBufferData(GL_ARRAY_BUFFER, bytesToAllocate, vertexData.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::DisableAttributes() const
{
	for (const std::pair<const std::string, VertexAttribute>& item : m_attributeMap) {
		const auto& attr = item.second;
		glDisableVertexAttribArray(attr.index);
	}
}

void VertexBuffer::StaticAllocate(const std::string& bufferName, const std::vector<unsigned short int>& indexData)
{
	m_indexCount = indexData.size();
	unsigned long long bytesToAllocate = indexData.size() * sizeof(unsigned short int);
	Select(bufferName);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, bytesToAllocate, indexData.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
