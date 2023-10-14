#include "GraphicsObject.h"
#include <cstdarg>

GraphicsObject::GraphicsObject()
{
	m_animation = nullptr;
}

GraphicsObject::~GraphicsObject()
{
}

void GraphicsObject::Update(double elapsedSeconds)
{
	if (m_animation != nullptr) {
		m_animation->Update(elapsedSeconds);
	}
}


