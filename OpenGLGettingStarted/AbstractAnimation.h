#pragma once
#include <memory>
class GraphicsObject;

class AbstractAnimation
{
protected:
	std::shared_ptr<GraphicsObject> m_object;

public:
	AbstractAnimation();
	virtual ~AbstractAnimation();
	virtual void SetObject(std::shared_ptr<GraphicsObject> object) { m_object = object; }
	virtual void Update(double elapsedSeconds) = 0;
};

