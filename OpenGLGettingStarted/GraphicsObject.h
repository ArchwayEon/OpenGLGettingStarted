#pragma once
#include <memory>
#include <glad/glad.h>
#include "GraphicsStructures.h"
#include "Mesh.h"

class GraphicsObject
{
private:
    GLuint m_vaoId;

public:
    Mesh mesh;

public:
    ~GraphicsObject();
    void CreateBuffers();
    void Render(unsigned int shaderProgramId);
};

