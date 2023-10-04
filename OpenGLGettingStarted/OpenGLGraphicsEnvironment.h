#pragma once
#include <memory>
#include "GlfwGraphicsWindow.h"
class OpenGLGraphicsEnvironment
{
protected:
	int m_majorVersion, m_minorVersion;
	std::shared_ptr<GlfwGraphicsWindow> m_window;

public:
	void SetVersion(int majorVersion, int minorVersion);
	void SetGraphicsWindow(std::shared_ptr<AbstractGraphicsWindow> window);
	void Initialize();
	void Run();
};

