#pragma once
#include <memory>
#include <glad/glad.h>
#include "GraphicsStructures.h"
#include "Mesh.h"
#include "VertexArray.h"

class GraphicsObject
{
protected:
    std::unique_ptr<Mesh> m_mesh;

public:
    std::shared_ptr<VertexArray> vertexArray;

public:
    GraphicsObject();
    ~GraphicsObject();
    void SetMesh(std::unique_ptr<Mesh> mesh);
    void AllocateMeshes();
    void Render(unsigned int shaderProgramId);
};

