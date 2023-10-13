#include <GLFW/glfw3.h>
#include "GlfwGraphicsWindow.h"

GlfwGraphicsWindow::GlfwGraphicsWindow(string title, int width, int height) :
	AbstractGraphicsWindow(title, width, height)
{
	m_openglMajorVersion = 4;
	m_openglMinorVersion = 6;
	m_window = nullptr;
}

GlfwGraphicsWindow::~GlfwGraphicsWindow()
{
	glfwTerminate();
}

void GlfwGraphicsWindow::SetOpenGLVersion(int majorVersion, int minorVersion)
{
	m_openglMajorVersion = majorVersion;
	m_openglMinorVersion = minorVersion;
}

void GlfwGraphicsWindow::SetupFramebufferSizeCallback()
{
	glfwSetFramebufferSizeCallback(m_window, framebufferSizeCallback);
}

void GlfwGraphicsWindow::Initialize()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, m_openglMajorVersion);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, m_openglMinorVersion);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

bool GlfwGraphicsWindow::Create()
{
	m_window = glfwCreateWindow(m_width, m_height, m_title.c_str(), nullptr, nullptr);
	if (m_window == nullptr) return false;
	glfwMakeContextCurrent(m_window);
	return true;
}

bool GlfwGraphicsWindow::IsTimeToClose()
{
	return glfwWindowShouldClose(m_window);
}

void GlfwGraphicsWindow::CheckInputs()
{
	if (glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(m_window, true);
	}
	if (glfwGetKey(m_window, GLFW_KEY_F1) == GLFW_PRESS) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	if (glfwGetKey(m_window, GLFW_KEY_F2) == GLFW_PRESS) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
}

unsigned int GlfwGraphicsWindow::GetKeyState(unsigned int whichKey)
{
	return glfwGetKey(m_window, whichKey);
}

void GlfwGraphicsWindow::Clear()
{
	glClearColor(
		backgroundColor.red,
		backgroundColor.green,
		backgroundColor.blue,
		backgroundColor.alpha
	);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

void GlfwGraphicsWindow::NextFrame()
{
	glfwSwapBuffers(m_window);
	glfwPollEvents();
}

void GlfwGraphicsWindow::GetWindowSize()
{
	glfwGetWindowSize(m_window, &m_width, &m_height);
}

void GlfwGraphicsWindow::framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}
