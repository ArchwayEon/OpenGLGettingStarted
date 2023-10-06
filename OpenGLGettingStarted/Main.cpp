#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "opengl32.lib")
#include <Windows.h>
#include <glad/glad.h> 
#include <GLFW/glfw3.h>

#include <iostream>
#include "GlfwGraphicsWindow.h"
#include "OpenGLGraphicsEnvironment.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    Logger logger;
    auto oglEnvironment = make_unique<OpenGLGraphicsEnvironment>(logger);
    oglEnvironment->SetVersion(4, 6);
    auto glfwWindow = make_shared<GlfwGraphicsWindow>("My Graphics Window");
    oglEnvironment->SetGraphicsWindow(glfwWindow);
    oglEnvironment->Initialize();
    oglEnvironment->Run();
    return 0;
}

