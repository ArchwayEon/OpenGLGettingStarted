#include "VertexBuffer.h"
#include <glad/glad.h>

void VertexBuffer::Generate()
{
	glGenBuffers(1, &m_vboId);
}

void VertexBuffer::AddVertexAttribute(
	unsigned int index, int numberOfComponents, int type, int isNormalized, unsigned int bytesToNext, unsigned long long byteOffset)
{
	VertexAttribute attr{};
	attr.index = index;
	attr.numberOfComponents = numberOfComponents;
	attr.type = type;
	attr.isNormalized = isNormalized;
	attr.bytesToNext = bytesToNext;
	attr.byteOffset = (void*)byteOffset;
	m_attributes.push_back(attr);
}

void VertexBuffer::EnableAttributes()
{
	glBindBuffer(GL_ARRAY_BUFFER, m_vboId);
	std::vector<VertexAttribute>::iterator it;
	for (it = m_attributes.begin(); it != m_attributes.end(); ++it) {
		glEnableVertexAttribArray(it->index);
		glVertexAttribPointer(
			it->index, it->numberOfComponents, it->type, 
			it->isNormalized, it->bytesToNext, it->byteOffset
		);
	}
}

void VertexBuffer::StaticAllocate(std::vector<float> vertexData)
{
	unsigned long long bytesToAllocate = vertexData.size() * sizeof(float);
	glBindBuffer(GL_ARRAY_BUFFER, m_vboId);
	// Allocate memory in the GPU for the buffer bound to the binding target and then
	// copy the data
	glBufferData(GL_ARRAY_BUFFER, bytesToAllocate, vertexData.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void VertexBuffer::DisableAttributes()
{
	std::vector<VertexAttribute>::iterator it;
	for (it = m_attributes.begin(); it != m_attributes.end(); ++it) {
		glDisableVertexAttribArray(it->index);
	}
}
