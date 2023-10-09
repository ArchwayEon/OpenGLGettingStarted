#pragma once

class VertexArray
{
protected:
	unsigned int m_vaoId;

public:
	VertexArray();
	~VertexArray();
	void Select() const;
	void Unselect() const;
};

