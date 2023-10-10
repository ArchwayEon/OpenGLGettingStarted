#include "Generate.h"

std::shared_ptr<GraphicsObject> Generate::FlatSurface(float width, float depth, RGB color)
{
    auto flatSurface = std::make_shared<GraphicsObject>();
    flatSurface->vertexArray = std::make_shared<VertexArray>();

    float halfWidth = width / 2;
    float halfDepth = depth / 2;

    Position p0 = { -halfWidth, 0.0f, -halfDepth };
    Position p1 = { -halfWidth, 0.0f,  halfDepth };
    Position p2 = {  halfWidth, 0.0f,  halfDepth };
    Position p3 = {  halfWidth, 0.0f, -halfDepth };

    std::unique_ptr<Mesh> mesh = std::make_unique<Mesh>();
    mesh->AddVertex(p0, color);
    mesh->AddVertex(p1, color);
    mesh->AddVertex(p2, color);
    mesh->AddVertex(p0, color);
    mesh->AddVertex(p2, color);
    mesh->AddVertex(p3, color);
    mesh->vertexBuffer = std::make_unique<VertexBuffer>();
    mesh->vertexBuffer->vertexArray = flatSurface->vertexArray;
    unsigned int size6floats = sizeof(float) * 6;
    unsigned long long size3floats = sizeof(float) * 3;
    // Positions
    mesh->vertexBuffer->AddVertexAttribute(
        { 0, 3, GL_FLOAT, GL_FALSE, size6floats, 0 });
    // Color
    mesh->vertexBuffer->AddVertexAttribute(
        { 1, 3, GL_FLOAT, GL_FALSE, size6floats, (void*)size3floats });

    mesh->AddTriangleIndices(0, 1, 2);
    mesh->AddTriangleIndices(0, 2, 3);
    mesh->indexBuffer = std::make_unique<IndexBuffer>();

    flatSurface->SetMesh(std::move(mesh));

    return flatSurface;
}
