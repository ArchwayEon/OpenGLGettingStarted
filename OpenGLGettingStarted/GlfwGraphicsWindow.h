#pragma once
#include "AbstractGraphicsWindow.h"
class GlfwGraphicsWindow :  public AbstractGraphicsWindow
{
protected:
	int m_openglMajorVersion, m_openglMinorVersion;
	GLFWwindow* m_window;

public:
	GlfwGraphicsWindow(string title, int width = 800, int height = 600);
	~GlfwGraphicsWindow();

	void SetOpenGLVersion(int majorVersion, int minorVersion);
	void SetupFramebufferSizeCallback();
	void Initialize();
	bool Create();
	bool IsTimeToClose();
	void CheckInputs();
	void Clear();
	void NextFrame();
	void GetWindowSize();

private:
	static void framebufferSizeCallback(GLFWwindow* window, int width, int height);
};

