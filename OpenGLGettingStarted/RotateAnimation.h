#pragma once
#include <glm/glm.hpp>
#include "AbstractAnimation.h"

class RotateAnimation :
    public AbstractAnimation
{
protected:
    float m_degreesPerSecond;
    glm::vec3 m_axis;

public:
    RotateAnimation(float degreesPerSecond, const glm::vec3& axis);
    void Update(double elapsedSeconds);
};

