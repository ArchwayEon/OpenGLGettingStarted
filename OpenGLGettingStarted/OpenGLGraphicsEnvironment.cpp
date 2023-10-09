#include <Windows.h>
#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include "OpenGLGraphicsEnvironment.h"
#include "GraphicsObject.h"
#include "VertexArray.h"

OpenGLGraphicsEnvironment::OpenGLGraphicsEnvironment(Logger& logger) : 
    m_logger(logger), m_majorVersion(4), m_minorVersion(6)
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

    LoadShaders();

    m_triangle = make_unique<GraphicsObject>();
    m_triangle->vertexArray = std::make_shared<VertexArray>();
    m_triangle->shader = m_shaders["basic"];

    std::unique_ptr<Mesh> triangleMesh = std::make_unique<Mesh>();
    triangleMesh->AddVertexData(3, 0.0f, 0.5f, 0.0f);
    triangleMesh->AddVertexData(3, 1.0f, 0.0f, 0.0f);
    triangleMesh->AddVertexData(3, -0.5f, -0.5f, 0.0f);
    triangleMesh->AddVertexData(3, 0.0f, 0.0f, 1.0f);
    triangleMesh->AddVertexData(3, 0.5f, -0.5f, 0.0f);
    triangleMesh->AddVertexData(3, 0.0f, 1.0f, 0.0f);
    triangleMesh->SetNumberOfVertices(3);
    triangleMesh->vertexBuffer = std::make_unique<VertexBuffer>();
    triangleMesh->vertexBuffer->vertexArray = m_triangle->vertexArray;
    unsigned int size6floats = sizeof(float) * 6;
    unsigned long long size3floats = sizeof(float) * 3;
    // Positions
    triangleMesh->vertexBuffer->AddVertexAttribute(
        {0, 3, GL_FLOAT, GL_FALSE, size6floats, 0});
    // Color
    triangleMesh->vertexBuffer->AddVertexAttribute(
        {1, 3, GL_FLOAT, GL_FALSE, size6floats, (void*)size3floats});

    triangleMesh->AddIndexData(3, 0, 1, 2);
    triangleMesh->SetNumberOfIndices(3);
    triangleMesh->indexBuffer = std::make_unique<IndexBuffer>();

    m_triangle->SetMesh(std::move(triangleMesh));
    m_triangle->AllocateStaticBuffers();
}

void OpenGLGraphicsEnvironment::Run()
{
    m_window->SetupFramebufferSizeCallback();

    while (m_window->IsTimeToClose() == false) {
        m_window->CheckInputs();
        m_window->Clear();
        m_triangle->Render();
        m_window->NextFrame();
    }
}

void OpenGLGraphicsEnvironment::LoadShaders()
{
    CreateBasicShader();
}

void OpenGLGraphicsEnvironment::CreateBasicShader()
{
    auto shader = make_shared<Shader>(m_logger);
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

   shader->Create(vertexSourceCode, fragmentSourceCode);
   m_shaders["basic"] = shader;
}

