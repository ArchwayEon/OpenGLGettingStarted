#include "GraphicsObject.h"
#include <cstdarg>

GraphicsObject::~GraphicsObject()
{
	glDeleteVertexArrays(1, &m_vaoId);
}

void GraphicsObject::CreateBuffers()
{
	glGenVertexArrays(1, &m_vaoId);
	glBindVertexArray(m_vaoId);
	mesh.CreateBuffers();
}

void GraphicsObject::Render(unsigned int shaderProgramId)
{
	glBindVertexArray(m_vaoId);
	glUseProgram(shaderProgramId);

	mesh.Render(shaderProgramId);

	glUseProgram(0);
	glBindVertexArray(0);
}

