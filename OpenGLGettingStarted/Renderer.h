#pragma once
#include <memory>
#include <string>
#include <unordered_map>
#include "Shader.h"
#include "VertexBuffer.h"
#include "Camera.h"
class Renderer
{
protected:
	unsigned int m_vaoId;
	std::shared_ptr<Shader> m_shader;
	std::unordered_map<std::string, std::shared_ptr<VertexBuffer>> m_bufferMap;
	std::shared_ptr<Camera> m_camera;

public:
	Renderer();
	~Renderer();

	void SetShader(const std::shared_ptr<Shader>& shader) { m_shader = shader; }
	void SetCamera(const std::shared_ptr<Camera>& camera) { m_camera = camera; }
	void AddVertexBuffer(const std::string& key, const std::shared_ptr<VertexBuffer>& value);

	void Render() const;

protected:
	void SetAttributeInterpretation(const std::vector<VertexAttribute>& attributes) const;
};

