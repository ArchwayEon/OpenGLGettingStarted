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

void GraphicsObject::Render(std::shared_ptr<Camera> camera) const
{
	vertexArray->Select();
	shader->Select();
	shader->SendUniform("uProjection", camera->GetProjection());
	shader->SendUniform("uView", camera->GetView());
	shader->SendUniform("uWorld", m_mesh->frame.orientation);
	m_mesh->Render();
}

