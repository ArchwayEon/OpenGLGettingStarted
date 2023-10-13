#include "Shader.h"
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>
#include <memory>
#include "TextFileReader.h"

Shader::Shader(Logger& logger) : 
    m_logger(logger), m_programId(0)
{
}

bool Shader::ReadFromFile(const std::string& vertexSourceFilePath, const std::string& fragmentSourceFilePath)
{
    auto reader = std::make_unique<TextFileReader>();
    reader->SetFilePath(vertexSourceFilePath);
    if (reader->Read() == false) return false;
    std::string vertexSource = reader->GetData();
    
    reader->SetFilePath(fragmentSourceFilePath);
    if (reader->Read() == false) return false;
    std::string fragmentSource = reader->GetData();
    Create(vertexSource, fragmentSource);
    return true;
}

int Shader::Create(const std::string& vertexSourceCode, const std::string& fragmentSourceCode)
{
    unsigned int vertexShaderId = Compile(GL_VERTEX_SHADER, vertexSourceCode);
    if (vertexShaderId == 0) m_logger.Log("Could not create vertex shader!");
    unsigned int fragmentShaderId = Compile(GL_FRAGMENT_SHADER, fragmentSourceCode);
    if (fragmentShaderId == 0) m_logger.Log("Could not create fragment shader!");
    m_programId = Link(vertexShaderId, fragmentShaderId);
    glDeleteShader(vertexShaderId);
    glDeleteShader(fragmentShaderId);
    return m_programId;
}

void Shader::Select() const
{
    glUseProgram(m_programId);
}

void Shader::SendUniform(const std::string& uniformName, const glm::mat4& mat4) const
{
    unsigned int location = glGetUniformLocation(m_programId, uniformName.c_str());
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(mat4));
}

void Shader::SendUniform(const std::string& uniformName, float data) const
{
    unsigned int location = glGetUniformLocation(m_programId, uniformName.c_str());
    glUniform1f(location, data);
}

void Shader::SendUniform(const std::string& uniformName, const glm::vec3& vector) const
{
    unsigned int location = glGetUniformLocation(m_programId, uniformName.c_str());
    glUniform3fv(location, 1, glm::value_ptr(vector));
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
