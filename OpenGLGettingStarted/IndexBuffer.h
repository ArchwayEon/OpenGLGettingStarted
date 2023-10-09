#pragma once
#include <vector>
class IndexBuffer
{
protected:
	unsigned int m_iboId;

public:
	IndexBuffer();
	~IndexBuffer();
	void Select() const;
	void Unselect() const;
	void StaticAllocate(std::vector<unsigned short int> indexData);
};

