#pragma once
#include <memory>
#include <map>
#include "GlfwGraphicsWindow.h"
#include "GraphicsObject.h"
#include "Shader.h"

class OpenGLGraphicsEnvironment
{
protected:
	Logger& m_logger;
	int m_majorVersion, m_minorVersion;
	std::shared_ptr<GlfwGraphicsWindow> m_window;
	//std::shared_ptr<Shader> m_shader;
	std::map<std::string,std::shared_ptr<Shader>> m_shaders;

	//GLuint m_shaderProgram;
	std::unique_ptr<GraphicsObject> m_triangle;

public:
	OpenGLGraphicsEnvironment(Logger& logger);
	void SetVersion(int majorVersion, int minorVersion);
	void SetGraphicsWindow(std::shared_ptr<AbstractGraphicsWindow> window);
	void Initialize();
	void Run();

private:
	void LoadShaders();
	void CreateBasicShader();
};

