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

    std::unique_ptr<Mesh> mesh = std::make_unique<Mesh>();
    mesh->AddVertex(p0, color);
    mesh->AddVertex(p1, color);
    mesh->AddVertex(p2, color);
    mesh->AddVertex(p3, color);

    mesh->AddTriangleIndices(0, 1, 2);
    mesh->AddTriangleIndices(2, 3, 0);

    flatSurface->mesh = std::move(mesh);

    return flatSurface;
}
