#pragma once
#include <glm\glm.hpp>
#include "GraphicsStructures.h"

class ReferenceFrame
{
public:
    glm::mat4 orientation;

public:
    ReferenceFrame() : orientation(1.0f) {}
    ~ReferenceFrame() {}

    void SetPosition(float x, float y, float z) {
        orientation[3] = glm::vec4(x, y, z, 1.0f);
    }
    void SetPosition(const glm::vec3& pos) {
        orientation[3] = glm::vec4(pos, 1.0f);
    }
    glm::vec3 GetPosition() const { return glm::vec3(orientation[3]); }
    glm::vec3 GetXAxis() const { return glm::vec3(orientation[0]); }
    glm::vec3 GetYAxis() const { return glm::vec3(orientation[1]); }
    glm::vec3 GetZAxis() const { return glm::vec3(orientation[2]); }

    void Reset() { orientation = glm::mat4(1.0f); }
    void Rotate(float degrees, const glm::vec3& axis);
    void RotateWorld(float degrees, const glm::vec3& axis);
    void Scale(float ratio);
    void Move(const glm::vec3& vector);
    void PointAt(float x, float y, float z);
    void PointAt(const glm::vec3& point);
};

