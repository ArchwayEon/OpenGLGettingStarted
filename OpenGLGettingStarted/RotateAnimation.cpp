#include "RotateAnimation.h"
#include "GraphicsObject.h"

RotateAnimation::RotateAnimation(float degreesPerSecond, const glm::vec3& axis) :
	m_degreesPerSecond(degreesPerSecond), m_axis(axis)
{
}

void RotateAnimation::Update(double elapsedSeconds)
{
	double deltaDegrees = 90 * elapsedSeconds;
	m_object->frame.Rotate((float)deltaDegrees, m_axis);
}
