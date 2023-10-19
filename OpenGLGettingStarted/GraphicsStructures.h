#pragma once
#ifndef GRAPHICS_STRUCTURES
#define GRAPHICS_STRUCTURES

#include <glm/glm.hpp>

struct RGB {
	float red, green, blue;
};

struct RGBA {
	float red, green, blue, alpha;
};

struct Position {
	float x, y, z;
};

struct Direction {
	float x, y, z;
};

struct Material {
	float ambientIntensity;
};

struct Light {
	glm::vec3 position;
	glm::vec3 color;
	float intensity;
};

struct PCNVertex {
	Position position;
	RGB color;
	Direction normal;
};

enum class ShadingType {
	Flat_Shading, Smooth_Shading
};


#endif
