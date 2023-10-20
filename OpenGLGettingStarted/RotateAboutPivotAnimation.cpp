#include "RotateAboutPivotAnimation.h"
#include "GraphicsObject.h"

RotateAboutPivotAnimation::RotateAboutPivotAnimation(
	const glm::vec3& pivotPoint, float degreesPerSecond, const glm::vec3& axis) :
	m_pivotPoint(pivotPoint), m_degreesPerSecond(degreesPerSecond), m_axis(axis)
{
}

void RotateAboutPivotAnimation::Update(double elapsedSeconds)
{
	double deltaDegrees = 90 * elapsedSeconds;
	m_object->frame.RotateAboutLocalPivot(m_pivotPoint, (float)deltaDegrees, m_axis);
}
