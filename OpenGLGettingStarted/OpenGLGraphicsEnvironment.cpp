#include <Windows.h>
#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include "OpenGLGraphicsEnvironment.h"
#include "GraphicsObject.h"
#include "VertexArray.h"
#include "Generate.h"
#include <iostream>

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

    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(MessageCallback, 0);

    // Cull back faces and use counter-clockwise winding of front faces
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);

    // Enable depth testing
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LEQUAL);
    glDepthRange(0.0f, 1.0f);

    m_camera = make_shared<Camera>();

    LoadShaders();
    LoadObjects();

    m_camera->frame.SetPosition(0.0f, 5.0f, 10.0f);
}

void OpenGLGraphicsEnvironment::Run()
{
    m_window->SetupFramebufferSizeCallback();

    while (m_window->IsTimeToClose() == false) {
        m_window->GetWindowSize();
        m_window->CheckInputs();
        
        //m_camera->SetupLookingForward();
        m_camera->SetupProjectionAndView(m_window->GetAspectRatio());

        m_window->Clear();
        m_currentScene->Render();
        m_window->NextFrame();
    }
}

void OpenGLGraphicsEnvironment::LoadObjects()
{
    m_currentScene = std::make_unique<Scene>();
    m_currentScene->camera = m_camera;

    m_allObjects["triangle"] = std::make_shared<GraphicsObject>();
    m_allObjects["triangle"]->vertexArray = std::make_shared<VertexArray>();
    

    std::unique_ptr<Mesh> triangleMesh = std::make_unique<Mesh>();
    triangleMesh->AddVertexData(3, 0.0f, 0.5f, 0.0f);
    triangleMesh->AddVertexData(3, 1.0f, 0.0f, 0.0f);
    triangleMesh->AddVertexData(3, -0.5f, -0.5f, 0.0f);
    triangleMesh->AddVertexData(3, 0.0f, 0.0f, 1.0f);
    triangleMesh->AddVertexData(3, 0.5f, -0.5f, 0.0f);
    triangleMesh->AddVertexData(3, 0.0f, 1.0f, 0.0f);
    triangleMesh->SetNumberOfVertices(3);
    triangleMesh->vertexBuffer = std::make_unique<VertexBuffer>();
    triangleMesh->vertexBuffer->vertexArray = m_allObjects["triangle"]->vertexArray;
    unsigned int size6floats = sizeof(float) * 6;
    unsigned long long size3floats = sizeof(float) * 3;
    // Positions
    triangleMesh->vertexBuffer->AddVertexAttribute(
        { 0, 3, GL_FLOAT, GL_FALSE, size6floats, 0 });
    // Color
    triangleMesh->vertexBuffer->AddVertexAttribute(
        { 1, 3, GL_FLOAT, GL_FALSE, size6floats, (void*)size3floats });

    triangleMesh->AddTriangleIndices(0, 1, 2);
    triangleMesh->indexBuffer = std::make_unique<IndexBuffer>();

    m_allObjects["triangle"]->SetMesh(std::move(triangleMesh));
    m_allObjects["triangle"]->AllocateStaticBuffers();
    m_allObjects["triangle"]->shader = m_shaders["basic3d"];
    m_currentScene->AddObject("triangle", m_allObjects["triangle"]);


    m_allObjects["flatsurface"] = Generate::FlatSurface(10, 10, { 0.0f, 0.5f, 0.0f });
    m_allObjects["flatsurface"]->shader = m_shaders["basic3d"];
    m_allObjects["flatsurface"]->AllocateStaticBuffers();
    m_currentScene->AddObject("flatsurface", m_allObjects["flatsurface"]);

}

void OpenGLGraphicsEnvironment::LoadShaders()
{
    CreateBasicShader();
    CreateBasic3DShader();
}

void OpenGLGraphicsEnvironment::CreateBasicShader()
{
    auto shader = make_shared<Shader>(m_logger);
    std::string vertexSourceCode =
        "#version 460\n"\
        "layout(location = 0) in vec3 position;\n"\
        "layout(location = 1) in vec3 vertexColor;\n"\
        "out vec4 fragColor;\n"\
        "void main()\n"\
        "{\n"\
        "   gl_Position = vec4(position, 1.0);\n" \
        "   fragColor = vec4(vertexColor, 1.0);\n" \
        "}\n";
    std::string fragmentSourceCode =
        "#version 460\n"\
        "in vec4 fragColor;\n"\
        "out vec4 color;\n"\
        "void main()\n"\
        "{\n"\
        "   color = fragColor;\n"\
        "}\n";

   shader->Create(vertexSourceCode, fragmentSourceCode);
   m_shaders["basic"] = shader;
}

void OpenGLGraphicsEnvironment::CreateBasic3DShader()
{
    auto shader = make_shared<Shader>(m_logger);
    std::string vertexSourceCode =
        "#version 460\n"\
        "layout(location = 0) in vec3 position;\n"\
        "layout(location = 1) in vec3 vertexColor;\n"\
        "out vec4 fragColor;\n"\
        "uniform mat4 uWorld;\n"\
        "uniform mat4 uView;\n"\
        "uniform mat4 uProjection;\n"\
        "void main()\n"\
        "{\n"\
        "   gl_Position = uProjection * uView * uWorld * vec4(position, 1.0);\n" \
        "   fragColor = vec4(vertexColor, 1.0);\n" \
        "}\n";
    std::string fragmentSourceCode =
        "#version 460\n"\
        "in vec4 fragColor;\n"\
        "out vec4 color;\n"\
        "void main()\n"\
        "{\n"\
        "   color = fragColor;\n"\
        "}\n";

    shader->Create(vertexSourceCode, fragmentSourceCode);
    m_shaders["basic3d"] = shader;
}

