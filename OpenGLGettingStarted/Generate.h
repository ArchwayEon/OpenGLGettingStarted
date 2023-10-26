#pragma once
#include <memory>
#include "GraphicsStructures.h"
#include "Mesh.h"


class Generate
{
public:
	static std::unique_ptr<Mesh> LineArrow(float length, RGB color);
	static std::unique_ptr<Mesh> FlatSurface(float width, float depth, RGB color);
	static std::unique_ptr<Mesh> Cuboid(float width, float height, float depth, RGB color);
	static std::unique_ptr<Mesh> Cylinder(float radius, float height, int slices, int stacks, RGB color, ShadingType shadingType);;
};

