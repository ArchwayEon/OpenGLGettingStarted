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
	switch (m_state) {
		case CameraState::NotMoving:
			break;
		case CameraState::MovingForward: {
			auto forward = -frame.GetZAxis();
			forward *= (2.0 * elapsedSeconds);
			frame.Move(forward);
			break;
		}
		case CameraState::MovingBackward: {
			auto backward = frame.GetZAxis();
			backward *= (2.0 * elapsedSeconds);
			frame.Move(backward);
			break;
		}
		case CameraState::MovingUp: {
			auto up = glm::vec3{ 0, 1, 0 };
			up *= (2.0 * elapsedSeconds);
			frame.Move(up);
			break;
		}
		case CameraState::MovingDown: {
			auto down = glm::vec3{ 0, -1, 0 };
			down *= (2.0 * elapsedSeconds);
			frame.Move(down);
			break;
		}
		case CameraState::TurningRight: {
			auto turnAngle = -90.0 * elapsedSeconds;
			frame.Rotate((float)turnAngle, frame.GetYAxis());
			break;
		}
		case CameraState::TurningLeft: {
			auto turnAngle = 90.0 * elapsedSeconds;
			frame.Rotate((float)turnAngle, frame.GetYAxis());
			break;
		}
		case CameraState::StrafingRight: {
			auto right = frame.GetXAxis();
			right *= (2.0 * elapsedSeconds);
			frame.Move(right);
			break;
		}
		case CameraState::StrafingLeft: {
			auto left = -frame.GetXAxis();
			left *= (2.0 * elapsedSeconds);
			frame.Move(left);
			break;
		}
	}
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
