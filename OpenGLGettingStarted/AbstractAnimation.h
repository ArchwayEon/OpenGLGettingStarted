#pragma once
#include <memory>
class GraphicsObject;

class AbstractAnimation
{
protected:
	GraphicsObject* m_object;

public:
	AbstractAnimation();
	virtual ~AbstractAnimation();
	virtual void SetObject(GraphicsObject* object) { m_object = object; }
	virtual void Update(double elapsedSeconds) = 0;
};

