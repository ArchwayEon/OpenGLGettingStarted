#include "Renderer.h"
#include <glad/glad.h>

Renderer::Renderer() : m_vaoId(0)
{
	glGenVertexArrays(1, &m_vaoId);
}

Renderer::~Renderer()
{
	glDeleteVertexArrays(1, &m_vaoId);
}

void Renderer::AddVertexBuffer(const std::string& key, const std::shared_ptr<VertexBuffer>& value)
{
	m_bufferMap[key] = value;
}

void Renderer::Render() const
{
	glBindVertexArray(m_vaoId);
	glUseProgram(m_shader->GetProgramId());
	// Global uniforms
	m_shader->SendUniform("uProjection", m_camera->GetProjection());
	m_shader->SendUniform("uView", m_camera->GetView());
	for (const auto& element : m_bufferMap) {
		const auto& buffer = element.second;
		glBindBuffer(GL_ARRAY_BUFFER, buffer->GetVBOId());
		// Per object uniforms
		m_shader->SendUniform("uWorld", buffer->attachedObject->frame.orientation);
		SetAttributeInterpretation(buffer->GetAttributes());
		if (buffer->IsIndexed()) {
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer->GetIBOId());
			glDrawElements(
				buffer->GetPrimitiveType(), 
				(GLsizei)buffer->GetIndexCount(), 
				GL_UNSIGNED_SHORT, 0);
		}
		else {
			glDrawArrays(buffer->GetPrimitiveType(), 0, (GLsizei)buffer->GetVertexCount());
		}
	}
}

void Renderer::SetAttributeInterpretation(const std::vector<VertexAttribute>& attributes) const
{
	for (unsigned int i = 0; i < attributes.size(); i++) {
		const auto& attr = attributes[i];
		glEnableVertexAttribArray(attr.index);
		glVertexAttribPointer(
			attr.index, attr.numberOfComponents, attr.type,
			attr.isNormalized, attr.bytesToNext, attr.byteOffset
		);
	}
}
