#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "opengl32.lib")
#include <Windows.h>
#include <glad/glad.h> 
#include <GLFW/glfw3.h>

#include <iostream>
#include "GlfwGraphicsWindow.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    auto glfwWindow = make_unique<GlfwGraphicsWindow>("My Graphics Window");
    glfwWindow->SetOpenGLVersion(4, 6);
    glfwWindow->Initialize();

    bool created = glfwWindow->Create();
    if (created == false) {
        std::cout << "Failed to create GLFW window" << std::endl;
        return -1;
    }

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glfwWindow->SetupFramebufferSizeCallback();

    while(glfwWindow->IsTimeToClose() == false){
        glfwWindow->CheckInputs();
        glfwWindow->Clear();
        glfwWindow->NextFrame();
    }

    return 0;
}

