#pragma once
#include <string>
#include <glad/glad.h>
#include "Logger.h"
class Shader
{
protected:
	Logger& m_logger;

public:
	Shader(Logger& logger);
	virtual ~Shader() = default;
	int Create(const std::string& vertexSourceCode, const std::string& fragmentSourceCode);

protected:
	int Compile(unsigned int type, const std::string& sourceCode);
	int Link(unsigned int vertexShaderId, unsigned int fragmentShaderId);
	void LogError(unsigned int programId, PFNGLGETSHADERIVPROC glGetIV, PFNGLGETSHADERINFOLOGPROC glGetInfoLog);
};
