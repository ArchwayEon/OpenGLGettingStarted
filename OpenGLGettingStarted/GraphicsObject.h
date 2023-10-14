#pragma once
#include <memory>
#include <glad/glad.h>
#include "Mesh.h"
#include "ReferenceFrame.h"
#include "AbstractAnimation.h"

class GraphicsObject
{
protected:
    std::unique_ptr<AbstractAnimation> m_animation;

public:
    ReferenceFrame frame;
    std::unique_ptr<Mesh> mesh;

public:
    GraphicsObject();
    virtual ~GraphicsObject();
    void SetAnimation(std::unique_ptr<AbstractAnimation> animation) {
        m_animation = std::move(animation);
        m_animation->SetObject(std::shared_ptr<GraphicsObject>(this));
    }
    void Update(double elapsedSeconds);
};