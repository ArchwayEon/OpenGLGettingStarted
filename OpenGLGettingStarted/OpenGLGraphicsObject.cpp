#include "OpenGLGraphicsObject.h"

OpenGLGraphicsObject::~OpenGLGraphicsObject()
{
	glDeleteVertexArrays(1, &m_vaoId);
}

void OpenGLGraphicsObject::SetVertices(std::unique_ptr<Vertex[]> vertices, GLsizei size)
{
	m_vertices = std::move(vertices);
	m_arraySize = size;
}

void OpenGLGraphicsObject::Setup()
{
	glGenVertexArrays(1, &m_vaoId);
	glBindVertexArray(m_vaoId);
	// Declare the buffer object and store a handle to the object
	glGenBuffers(1, &m_vboId);
	// Bind the object to the binding target
	glBindBuffer(GL_ARRAY_BUFFER, m_vboId);
	// Allocate memory in the GPU for the buffer bound to the binding target and then
	// copy the data
	glBufferData(GL_ARRAY_BUFFER, m_arraySize * sizeof(Vertex), m_vertices.get(), GL_STATIC_DRAW);
	// Good practice to cleanup by unbinding 
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

}

void OpenGLGraphicsObject::Render(unsigned int shaderProgramId)
{
	glBindVertexArray(m_vaoId);
	glUseProgram(shaderProgramId);

	glBindBuffer(GL_ARRAY_BUFFER, m_vboId);
	// Positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(
		0,
		3,              // Each position has 3 components
		GL_FLOAT,       // Each component is a 32-bit floating point value
		GL_FALSE,
		sizeof(Vertex), // The number of bytes to the next position
		(void*)0        // Byte offset of the first position in the array
	);
	// Colors
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(
		1,
		3,                          // Each color has 3 components
		GL_FLOAT,                   // Each component is a 32-bit floating point value
		GL_FALSE,
		sizeof(Vertex),             // The number of bytes to the next color
		(void*)(sizeof(GLfloat) * 3) // Byte offset of the first color in the array
	);
	glDrawArrays(GL_TRIANGLES, 0, m_arraySize);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glUseProgram(0);
	glBindVertexArray(0);
}
