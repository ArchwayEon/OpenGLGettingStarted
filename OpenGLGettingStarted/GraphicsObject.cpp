#include "GraphicsObject.h"
#include <cstdarg>

GraphicsObject::GraphicsObject()
{
}

GraphicsObject::~GraphicsObject()
{
}

void GraphicsObject::SetMesh(std::unique_ptr<Mesh> mesh)
{
	m_mesh = std::move(mesh);
}

void GraphicsObject::AllocateMeshes()
{
	m_mesh->AllocateStaticBuffers();
}

void GraphicsObject::Render(unsigned int shaderProgramId)
{
	vertexArray->Select();
	glUseProgram(shaderProgramId);

	m_mesh->Render(shaderProgramId);

	glUseProgram(0);
	glBindVertexArray(0);
}

