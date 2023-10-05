#pragma once
class AbstractGraphicsObject
{
public:
	virtual ~AbstractGraphicsObject() = default;
	virtual void Setup() = 0;
	virtual void Render(unsigned int shaderProgramId) = 0;
};

