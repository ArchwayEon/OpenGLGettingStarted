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
	m_shader->SendUniform("uGlobalLightPosition", m_scene->globalLight.position);
	m_shader->SendUniform("uGlobalLightColor", m_scene->globalLight.color);
	m_shader->SendUniform("uGlobalLightIntensity", m_scene->globalLight.intensity);
	const auto& objectMap = m_scene->GetObjectMap();
	for (const auto& element : objectMap) {
		const auto& object = element.second;
		const auto& buffer = object->mesh->GetBuffer();
		buffer->Select("VBO");
		// Per object uniforms
		m_shader->SendUniform("uWorld", object->frame.orientation);
		m_shader->SendUniform("uMaterialAmbientIntensity", object->mesh->material.ambientIntensity);
		SetAttributeInterpretation(buffer->GetAttributes());
		if (buffer->IsIndexed()) {
			buffer->Select("IBO");
			glDrawElements(buffer->GetPrimitiveType(), (GLsizei)buffer->GetIndexCount(), 
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
