#include "Generate.h"

std::shared_ptr<GraphicsObject> Generate::FlatSurface(float width, float depth, RGB color)
{
    auto flatSurface = std::make_shared<GraphicsObject>();

    float halfWidth = width / 2;
    float halfDepth = depth / 2;

    Position p0 = { -halfWidth, 0.0f, -halfDepth };
    Position p1 = { -halfWidth, 0.0f,  halfDepth };
    Position p2 = {  halfWidth, 0.0f,  halfDepth };
    Position p3 = {  halfWidth, 0.0f, -halfDepth };

    Direction normal = { 0.0f, 1.0f, 0.0f };

    std::unique_ptr<Mesh> mesh = std::make_unique<Mesh>();
    mesh->AddVertex(p0, color, normal);
    mesh->AddVertex(p1, color, normal);
    mesh->AddVertex(p2, color, normal);
    mesh->AddVertex(p3, color, normal);
    mesh->AddTriangleIndices(0, 1, 2);
    mesh->AddTriangleIndices(2, 3, 0);

    flatSurface->mesh = std::move(mesh);

    return flatSurface;
}

std::shared_ptr<GraphicsObject> Generate::Cuboid(float width, float height, float depth, RGB color)
{
    auto cuboid = std::make_shared<GraphicsObject>();

    float halfWidth = width / 2;
    float halfDepth = depth / 2;
    float halfHeight = height / 2;

    Position p0 = { -halfWidth,  halfHeight, halfDepth };
    Position p1 = { -halfWidth, -halfHeight, halfDepth };
    Position p2 = {  halfWidth, -halfHeight, halfDepth };
    Position p3 = {  halfWidth,  halfHeight, halfDepth };

    Position p4 = { -halfWidth,  halfHeight, -halfDepth };
    Position p5 = { -halfWidth, -halfHeight, -halfDepth };
    Position p6 = {  halfWidth, -halfHeight, -halfDepth };
    Position p7 = {  halfWidth,  halfHeight, -halfDepth };

    std::unique_ptr<Mesh> mesh = std::make_unique<Mesh>();
    // Front face
    Direction normal = { 0, 0, -1 };
    mesh->AddVertex(p0, color, normal);
    mesh->AddVertex(p1, color, normal);
    mesh->AddVertex(p2, color, normal);
    mesh->AddVertex(p2, color, normal);
    mesh->AddVertex(p3, color, normal);
    mesh->AddVertex(p0, color, normal);
    // Right face
    normal = { 1, 0, 0 };
    mesh->AddVertex(p3, color, normal);
    mesh->AddVertex(p2, color, normal);
    mesh->AddVertex(p6, color, normal);
    mesh->AddVertex(p6, color, normal);
    mesh->AddVertex(p7, color, normal);
    mesh->AddVertex(p3, color, normal);
    // Back face
    normal = { 0, 0, 1 };
    mesh->AddVertex(p7, color, normal);
    mesh->AddVertex(p6, color, normal);
    mesh->AddVertex(p5, color, normal);
    mesh->AddVertex(p5, color, normal);
    mesh->AddVertex(p4, color, normal);
    mesh->AddVertex(p7, color, normal);
    // Left face
    normal = { -1, 0, 0 };
    mesh->AddVertex(p4, color, normal);
    mesh->AddVertex(p5, color, normal);
    mesh->AddVertex(p1, color, normal);
    mesh->AddVertex(p1, color, normal);
    mesh->AddVertex(p0, color, normal);
    mesh->AddVertex(p4, color, normal);
    // Top face
    normal = { 0, 1, 0 };
    mesh->AddVertex(p4, color, normal);
    mesh->AddVertex(p0, color, normal);
    mesh->AddVertex(p3, color, normal);
    mesh->AddVertex(p3, color, normal);
    mesh->AddVertex(p7, color, normal);
    mesh->AddVertex(p4, color, normal);
    // Bottom face
    normal = { 0, -1, 0 };
    mesh->AddVertex(p6, color, normal);
    mesh->AddVertex(p2, color, normal);
    mesh->AddVertex(p1, color, normal);
    mesh->AddVertex(p1, color, normal);
    mesh->AddVertex(p5, color, normal);
    mesh->AddVertex(p6, color, normal);

    //mesh->AddVertex(p3, color);
    //mesh->AddVertex(p4, color);
    //mesh->AddVertex(p5, color);
    //mesh->AddVertex(p6, color);
    //mesh->AddVertex(p7, color);
    //mesh->AddTriangleIndices(0, 1, 2);
    //mesh->AddTriangleIndices(2, 3, 0);
    //mesh->AddTriangleIndices(3, 2, 6);
    //mesh->AddTriangleIndices(6, 7, 3);
    //mesh->AddTriangleIndices(7, 6, 5);
    //mesh->AddTriangleIndices(5, 4, 7);
    //mesh->AddTriangleIndices(4, 5, 1);
    //mesh->AddTriangleIndices(1, 0, 4);
    //mesh->AddTriangleIndices(1, 5, 6);
    //mesh->AddTriangleIndices(6, 2, 1);
    //mesh->AddTriangleIndices(4, 0, 3);
    //mesh->AddTriangleIndices(3, 7, 4);

    cuboid->mesh = std::move(mesh);

    return cuboid;
}
