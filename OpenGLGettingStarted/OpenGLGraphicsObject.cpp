#include "OpenGLGraphicsObject.h"
#include <cstdarg>

OpenGLGraphicsObject::~OpenGLGraphicsObject()
{
	glDeleteVertexArrays(1, &m_vaoId);
}

void OpenGLGraphicsObject::CreateBuffers()
{
	glGenVertexArrays(1, &m_vaoId);
	glBindVertexArray(m_vaoId);
	vertexBuffer.Generate();
	vertexBuffer.StaticAllocate(m_vertexData);
	unsigned int size3floats = sizeof(float) * 3;
	unsigned int size6floats = sizeof(float) * 6;
	// Positions
	vertexBuffer.AddVertexAttribute(0, 3, GL_FLOAT, GL_FALSE, size6floats, 0);
	// Color
	vertexBuffer.AddVertexAttribute(1, 3, GL_FLOAT, GL_FALSE, size6floats, size3floats);
}

void OpenGLGraphicsObject::Render(unsigned int shaderProgramId)
{
	glBindVertexArray(m_vaoId);
	glUseProgram(shaderProgramId);

	vertexBuffer.EnableAttributes();
	glDrawArrays(GL_TRIANGLES, 0, m_numberOfVertices);
	vertexBuffer.DisableAttributes();

	glUseProgram(0);
	glBindVertexArray(0);
}

void OpenGLGraphicsObject::AddVertexData(int count, ...)
{
	va_list args;
	va_start(args, count);

	while(count > 0){
		// The default is double, so accept as double and then cast to
		// float.
		m_vertexData.push_back(static_cast<float>(va_arg(args, double)));
		count--;
	}

	va_end(args);
}
