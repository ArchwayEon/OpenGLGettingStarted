#pragma once
#include <memory>
#include <glad/glad.h>
#include "GraphicsStructures.h"
#include "Mesh.h"
#include "Shader.h"
#include "ReferenceFrame.h"

class GraphicsObject
{
protected:
    

public:
    std::shared_ptr<Shader> shader;
    ReferenceFrame frame;
    std::unique_ptr<Mesh> mesh;

public:
    GraphicsObject();
    ~GraphicsObject();
    void AllocateStaticBuffers();
};