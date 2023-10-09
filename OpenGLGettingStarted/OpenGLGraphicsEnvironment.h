#pragma once
#include <memory>
#include <map>
#include "GlfwGraphicsWindow.h"
#include "GraphicsObject.h"
#include "Shader.h"
#include "Scene.h"

class OpenGLGraphicsEnvironment
{
protected:
	Logger& m_logger;
	int m_majorVersion, m_minorVersion;
	std::shared_ptr<GlfwGraphicsWindow> m_window;
	std::map<std::string,std::shared_ptr<Shader>> m_shaders;
	std::unique_ptr<Scene> m_currentScene;
	std::map<std::string, std::shared_ptr<GraphicsObject>> m_allObjects;

public:
	OpenGLGraphicsEnvironment(Logger& logger);
	void SetVersion(int majorVersion, int minorVersion);
	void SetGraphicsWindow(std::shared_ptr<AbstractGraphicsWindow> window);
	void Initialize();
	void Run();

private:
	void LoadObjects();
	void LoadShaders();
	void CreateBasicShader();
};

