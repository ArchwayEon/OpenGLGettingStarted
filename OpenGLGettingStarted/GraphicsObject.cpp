#include "GraphicsObject.h"
#include <cstdarg>

GraphicsObject::GraphicsObject()
{
}

GraphicsObject::~GraphicsObject()
{
}

void GraphicsObject::Update(double elapsedSeconds)
{
	double deltaDegrees = 90 * elapsedSeconds;
	frame.Rotate((float)deltaDegrees, { 0, 1, 0 });
}


