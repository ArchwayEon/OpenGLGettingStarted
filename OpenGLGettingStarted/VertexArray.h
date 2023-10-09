#pragma once
//#include "VertexBuffer.h"
//#include "IndexBuffer.h"

class VertexArray
{
protected:
	unsigned int m_vaoId;
	//std::vector<VertexBuffer> m_vertexBuffers;
	//std::vector<IndexBuffer> m_indexBuffers;
	//std::vector<VertexAttribute> m_attributes;

public:
	VertexArray();
	~VertexArray();
	void Select() const;
	void Unselect() const;
	//void AddBuffer(const VertexBuffer& vb, const IndexBuffer& ib, const VertexAttribute& attr);
	//void EnableAttributes() const;
};

