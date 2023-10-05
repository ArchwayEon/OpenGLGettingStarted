#pragma once
#include <memory>
#include "GlfwGraphicsWindow.h"
#include "OpenGLGraphicsObject.h"

class OpenGLGraphicsEnvironment
{
protected:
	int m_majorVersion, m_minorVersion;
	std::shared_ptr<GlfwGraphicsWindow> m_window;

	GLuint m_shaderProgram;
	std::unique_ptr<OpenGLGraphicsObject> m_triangle;

public:
	void SetVersion(int majorVersion, int minorVersion);
	void SetGraphicsWindow(std::shared_ptr<AbstractGraphicsWindow> window);
	void Initialize();
	void Run();

	
	//void SetTriangle(std::unique_ptr<AbstractGraphicsObject> triangle);

private:
	void SetUpShaders();
	GLuint CompileShader(GLenum type, const GLchar* source);
	GLuint LinkShader(GLuint vertexShader, GLuint fragmentShader);
};

