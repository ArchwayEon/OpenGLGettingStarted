#include "GraphicsObject.h"
#include <cstdarg>

GraphicsObject::GraphicsObject()
{
}

GraphicsObject::~GraphicsObject()
{
}


void GraphicsObject::AllocateStaticBuffers()
{
	//vertexArray->Select();
	//mesh->AllocateStaticBuffers();
}

//void GraphicsObject::Render(std::shared_ptr<Camera> camera) const
//{
//	//vertexArray->Select();
//	//shader->Select();
//	//shader->SendUniform("uProjection", camera->GetProjection());
//	//shader->SendUniform("uView", camera->GetView());
//	//shader->SendUniform("uWorld", mesh->frame.orientation);
//	//mesh->Render();
//}

