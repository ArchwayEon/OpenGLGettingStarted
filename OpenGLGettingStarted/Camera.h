#pragma once
#include "ReferenceFrame.h"
#include <glm\glm.hpp>


enum class CameraState {
    NotMoving, MovingForward, MovingBackward, MovingUp, MovingDown,
    TurningRight, TurningLeft,
    StrafingRight, StrafingLeft
};

class Camera
{
protected:
    glm::mat4 m_projection, m_view;
    float m_aspectRatio;
    CameraState m_state;

public:
    float fieldOfView, nearPlane, farPlane;
    ReferenceFrame frame;
    glm::vec3 target;

public:
    Camera();
    ~Camera();

    virtual void Update(double elapsedSeconds);
    virtual const glm::mat4& GetProjection() const { return m_projection; }
    virtual const glm::mat4& GetView() const { return m_view; }
    virtual void SetupLookingForward();
    virtual void SetupProjectionAndView(float aspectRatio);
    virtual void SetState(CameraState state) { m_state = state; }
   
};
