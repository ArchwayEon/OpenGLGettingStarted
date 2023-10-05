#pragma once
#include <memory>
#include <glad/glad.h>
#include "AbstractGraphicsObject.h"
#include "GraphicsStructures.h"

class OpenGLGraphicsObject :
    public AbstractGraphicsObject
{
private:
    GLuint m_vaoId, m_vboId;
    GLsizei m_arraySize;
    std::unique_ptr<Vertex[]> m_vertices;

public:
    ~OpenGLGraphicsObject();
    void SetVertices(std::unique_ptr<Vertex[]> vertices, GLsizei size);
    void Setup();
    void Render(unsigned int shaderProgramId);
};

