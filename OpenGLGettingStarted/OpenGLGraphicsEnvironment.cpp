#include <Windows.h>
#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include "OpenGLGraphicsEnvironment.h"
#include "OpenGLGraphicsObject.h"

OpenGLGraphicsEnvironment::OpenGLGraphicsEnvironment(Logger& logger) : m_logger(logger)
{
}

void OpenGLGraphicsEnvironment::SetVersion(int majorVersion, int minorVersion)
{
	m_majorVersion = majorVersion;
	m_minorVersion = minorVersion;
}

void OpenGLGraphicsEnvironment::SetGraphicsWindow(std::shared_ptr<AbstractGraphicsWindow> window)
{
	m_window = dynamic_pointer_cast<GlfwGraphicsWindow>(window);
}

void OpenGLGraphicsEnvironment::Initialize()
{
    m_window->SetOpenGLVersion(m_majorVersion, m_minorVersion);

    m_window->Initialize();

    bool created = m_window->Create();
    if (created == false) {
        throw "Failed to create the graphics window.";
    }

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        throw "Failed to initialize GLAD.";
    }

    SetUpShaders();

    m_triangle = make_unique<OpenGLGraphicsObject>();
    m_triangle->AddVertexData(3, 0.0f, 0.5f, 0.0f);
    m_triangle->AddVertexData(3, 1.0f, 0.0f, 0.0f);
    m_triangle->AddVertexData(3, -0.5f, -0.5f, 0.0f);
    m_triangle->AddVertexData(3, 0.0f, 0.0f, 1.0f);
    m_triangle->AddVertexData(3, 0.5f, -0.5f, 0.0f);
    m_triangle->AddVertexData(3, 0.0f, 1.0f, 0.0f);
    m_triangle->SetNumberOfVertices(3);
    m_triangle->CreateBuffers();
}

void OpenGLGraphicsEnvironment::Run()
{
    m_window->SetupFramebufferSizeCallback();

    while (m_window->IsTimeToClose() == false) {
        m_window->CheckInputs();
        m_window->Clear();
        m_triangle->Render(m_shaderProgram);
        m_window->NextFrame();
    }
}

void OpenGLGraphicsEnvironment::SetUpShaders()
{
    m_shader = make_unique<Shader>(m_logger);
    std::string vertexSourceCode =
        "#version 400\n"\
        "layout(location = 0) in vec3 position;\n"\
        "layout(location = 1) in vec3 vertexColor;\n"\
        "out vec4 fragColor;\n"\
        "void main()\n"\
        "{\n"\
        "   gl_Position = vec4(position, 1.0);\n" \
        "   fragColor = vec4(vertexColor, 1.0);\n" \
        "}\n";
    std::string fragmentSourceCode =
        "#version 400\n"\
        "in vec4 fragColor;\n"\
        "out vec4 color;\n"\
        "void main()\n"\
        "{\n"\
        "   color = fragColor;\n"\
        "}\n";

    m_shaderProgram = m_shader->Create(vertexSourceCode, fragmentSourceCode);
}

