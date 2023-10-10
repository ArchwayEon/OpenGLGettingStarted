#pragma once
#include <memory>
#include "GraphicsStructures.h"
#include "GraphicsObject.h"
class Generate
{
public:
	static std::shared_ptr<GraphicsObject> FlatSurface(float width, float depth, RGB color);
};

