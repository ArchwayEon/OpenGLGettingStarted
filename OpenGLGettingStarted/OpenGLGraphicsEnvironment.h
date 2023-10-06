#pragma once
#include <memory>
#include "GlfwGraphicsWindow.h"
#include "OpenGLGraphicsObject.h"
#include "Shader.h"

class OpenGLGraphicsEnvironment
{
protected:
	Logger& m_logger;
	int m_majorVersion, m_minorVersion;
	std::shared_ptr<GlfwGraphicsWindow> m_window;
	std::unique_ptr<Shader> m_shader;

	GLuint m_shaderProgram;
	std::unique_ptr<OpenGLGraphicsObject> m_triangle;

public:
	OpenGLGraphicsEnvironment(Logger& logger);
	void SetVersion(int majorVersion, int minorVersion);
	void SetGraphicsWindow(std::shared_ptr<AbstractGraphicsWindow> window);
	void Initialize();
	void Run();

private:
	void SetUpShaders();
};

