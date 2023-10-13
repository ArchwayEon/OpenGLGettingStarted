#pragma once
#include <memory>
#include <glad/glad.h>
#include "Mesh.h"
#include "ReferenceFrame.h"

class GraphicsObject
{
protected:

public:
    ReferenceFrame frame;
    std::unique_ptr<Mesh> mesh;

public:
    GraphicsObject();
    ~GraphicsObject();
    void Update(double elapsedSeconds);
};