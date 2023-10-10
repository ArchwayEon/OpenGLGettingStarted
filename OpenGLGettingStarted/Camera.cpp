#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera() :
	fieldOfView(60.0f), m_aspectRatio(1.0f),
	nearPlane(0.1f), farPlane(50.0f), frame(),
	target({ 0.0f, 0.0f, 0.0f }),
	m_projection(1.0f), m_view(1.0f)
{
	frame.SetPosition(0.0f, 0.0f, 5.0f);
}

Camera::~Camera()
{
}

void Camera::Update(double elapsedSeconds)
{
}

void Camera::SetupLookingForward()
{
	glm::vec3 position = frame.GetPosition();
	glm::vec3 forward = frame.orientation[2];
	forward = -forward;
	target = position + forward;
}

void Camera::SetupProjectionAndView(float aspectRatio)
{
	m_aspectRatio = aspectRatio;
	m_projection = glm::perspective(
		glm::radians(fieldOfView),
		m_aspectRatio,
		nearPlane,
		farPlane
	);
	glm::vec3 position = frame.GetPosition();
	m_view = glm::lookAt(
		position,
		target,
		frame.GetYAxis()
	);
}
