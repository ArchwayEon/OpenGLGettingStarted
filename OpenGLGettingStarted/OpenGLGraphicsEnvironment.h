#pragma once
#include <memory>
#include <map>
#include "GraphicsObject.h"
#include "Shader.h"
#include "Scene.h"
#include "Camera.h"
#include "Renderer.h"
class GlfwGraphicsWindow;
class AbstractGraphicsWindow;

class OpenGLGraphicsEnvironment
{
protected:
	Logger& m_logger;
	int m_majorVersion, m_minorVersion;
	std::shared_ptr<GlfwGraphicsWindow> m_window;
	std::map<std::string,std::shared_ptr<Shader>> m_shaders;
	std::shared_ptr<Scene> m_currentScene;
	std::map<std::string, std::shared_ptr<GraphicsObject>> m_allObjects;
	std::shared_ptr<Camera> m_camera;
	std::unique_ptr<Renderer> m_renderer;

public:
	OpenGLGraphicsEnvironment(Logger& logger);
	void SetVersion(int majorVersion, int minorVersion);
	void SetGraphicsWindow(std::shared_ptr<AbstractGraphicsWindow> window);
	void Initialize();
	void Run();
	void CheckKeyState();

protected:
	void LoadObjects();
	void LoadShaders();
	void CreateBasicShader();
	void CreateBasic3DShader();
	void CreateBasic3DLightingShader();
	void ReadShadersFromFiles(const std::string& vertexFilePath, const std::string& fragmentFilePath);
	
	static void GLAPIENTRY
		MessageCallback(GLenum source,
			GLenum type,
			GLuint id,
			GLenum severity,
			GLsizei length,
			const GLchar* message,
			const void* userParam)
	{
		fprintf(stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
			(type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""),
			type, severity, message);
	}
};

