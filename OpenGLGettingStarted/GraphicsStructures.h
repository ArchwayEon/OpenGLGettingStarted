#pragma once
#ifndef GRAPHICS_STRUCTURES
#define GRAPHICS_STRUCTURES

struct RGB {
	float red, green, blue;
};

struct RGBA {
	float red, green, blue, alpha;
};

struct Position {
	float x, y, z;
};

struct Vertex {
	float x, y, z;
	float red, green, blue;
};

#endif
