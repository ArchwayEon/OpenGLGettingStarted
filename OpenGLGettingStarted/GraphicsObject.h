#pragma once
#include <memory>
#include <glad/glad.h>
#include "GraphicsStructures.h"
#include "Mesh.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Camera.h"

class GraphicsObject
{
protected:
    std::unique_ptr<Mesh> m_mesh;

public:
    std::shared_ptr<VertexArray> vertexArray;
    std::shared_ptr<Shader> shader;

public:
    GraphicsObject();
    ~GraphicsObject();
    void SetMesh(std::unique_ptr<Mesh> mesh);
    void AllocateStaticBuffers();
    void Render(std::shared_ptr<Camera> camera) const;
};