#pragma once
#include <string>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include "Logger.h"
class Shader
{
protected:
	Logger& m_logger;
	unsigned int m_programId;

public:
	Shader(Logger& logger);
	virtual ~Shader() = default;
	int Create(const std::string& vertexSourceCode, const std::string& fragmentSourceCode);
	inline unsigned int GetProgramId() const { return m_programId; }
	void Select() const;
	void SendUniform(const std::string& uniformName, const glm::mat4& mat4) const;
	void SendUniform(const std::string& uniformName, float data) const;
	void SendUniform(const std::string& uniformName, const glm::vec3& vector) const;

protected:
	int Compile(unsigned int type, const std::string& sourceCode);
	int Link(unsigned int vertexShaderId, unsigned int fragmentShaderId);
	void LogError(unsigned int programId, PFNGLGETSHADERIVPROC glGetIV, PFNGLGETSHADERINFOLOGPROC glGetInfoLog);
};

