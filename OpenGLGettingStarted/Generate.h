#pragma once
#include <memory>
#include "GraphicsStructures.h"
#include "GraphicsObject.h"


class Generate
{
public:
	static std::shared_ptr<GraphicsObject> LineArrow(float length, RGB color);
	static std::shared_ptr<GraphicsObject> FlatSurface(float width, float depth, RGB color);
	static std::shared_ptr<GraphicsObject> Cuboid(float width, float height, float depth, RGB color);
	static std::shared_ptr<GraphicsObject> Cylinder(float radius, float height, int slices, int stacks, RGB color, ShadingType shadingType);;
};

