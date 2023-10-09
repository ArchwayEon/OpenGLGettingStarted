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

void GraphicsObject::AllocateStaticBuffers()
{
	m_mesh->AllocateStaticBuffers();
}

void GraphicsObject::Render() const
{
	vertexArray->Select();
	shader->Select();
	m_mesh->Render();
}

