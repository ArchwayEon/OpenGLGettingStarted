#include "Shader.h"
#include <glad/glad.h>

Shader::Shader(Logger& logger) : m_logger(logger)
{
}

int Shader::Create(const std::string& vertexSourceCode, const std::string& fragmentSourceCode)
{
    unsigned int vertexShaderId = Compile(GL_VERTEX_SHADER, vertexSourceCode);
    if (vertexShaderId == 0) m_logger.Log("Could not create vertex shader!");
    unsigned int fragmentShaderId = Compile(GL_FRAGMENT_SHADER, fragmentSourceCode);
    if (fragmentShaderId == 0) m_logger.Log("Could not create fragment shader!");
    unsigned int shaderProgram = Link(vertexShaderId, fragmentShaderId);
    glDeleteShader(vertexShaderId);
    glDeleteShader(fragmentShaderId);
    return shaderProgram;
}

int Shader::Compile(unsigned int type, const std::string& sourceCode)
{
    const char* source = sourceCode.c_str();
    int length = (int)(sizeof(char) * strlen(source));
    unsigned int shaderId = glCreateShader(type);
    glShaderSource(shaderId, 1, (const char**)&source, &length);
    glCompileShader(shaderId);
    GLint shaderOk = 0;
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &shaderOk);
    if (!shaderOk) {
        m_logger.Log("Shader::Compile - Failed to compile the shader!");
        LogError(shaderId, glGetShaderiv, glGetShaderInfoLog);
        glDeleteShader(shaderId);
        shaderId = 0;
    }
    return shaderId;
}

int Shader::Link(unsigned int vertexShaderId, unsigned int fragmentShaderId)
{
    unsigned int programId = glCreateProgram();
    glAttachShader(programId, vertexShaderId);
    glAttachShader(programId, fragmentShaderId);
    glLinkProgram(programId);
    GLint programOk = 0;
    glGetProgramiv(programId, GL_LINK_STATUS, &programOk);
    if (!programOk) {
        m_logger.Log("Shader::Link - Failed to link the shaders!");
        LogError(programId, glGetProgramiv, glGetProgramInfoLog);
        glDeleteShader(programId);
        programId = 0;
    }
    return programId;
}

void Shader::LogError(unsigned int programId, PFNGLGETSHADERIVPROC glGetIV, PFNGLGETSHADERINFOLOGPROC glGetInfoLog)
{
    int logLength;
    glGetIV(programId, GL_INFO_LOG_LENGTH, &logLength);
    char* info = (char*)malloc(logLength);
    glGetInfoLog(programId, logLength, NULL, info);
    if (info != nullptr) {
        m_logger.Log(std::string(info));
    }
    free(info);
}
