#pragma once
#include <memory>
#include <glad/glad.h>
#include "AbstractGraphicsObject.h"
#include "GraphicsStructures.h"
#include "VertexBuffer.h"

class OpenGLGraphicsObject :
    public AbstractGraphicsObject
{
private:
    GLuint m_vaoId;
    GLsizei m_numberOfVertices;
    std::vector<float> m_vertexData;

public:
    VertexBuffer vertexBuffer;

public:
    ~OpenGLGraphicsObject();
    void SetNumberOfVertices(int numberOfVertices) { m_numberOfVertices = numberOfVertices; }
    void CreateBuffers();
    void Render(unsigned int shaderProgramId);
    void AddVertexData(int count, ...);
};

