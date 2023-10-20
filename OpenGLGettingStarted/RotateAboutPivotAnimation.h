#pragma once
#include <glm/glm.hpp>
#include "AbstractAnimation.h"

class RotateAboutPivotAnimation :
    public AbstractAnimation
{
protected:
    float m_degreesPerSecond;
    glm::vec3 m_axis;
    glm::vec3 m_pivotPoint;

public:
    RotateAboutPivotAnimation(const glm::vec3& pivotPoint, float degreesPerSecond, const glm::vec3& axis);
    void Update(double elapsedSeconds);
};

