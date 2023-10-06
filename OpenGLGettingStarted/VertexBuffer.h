#pragma once
#include <vector>

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

public:
	void AddVertexAttribute(unsigned int index, int numberOfComponents, int type, int isNormalized, unsigned int bytesToNext, int offset);
};

