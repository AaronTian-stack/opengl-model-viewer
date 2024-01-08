#include "camera.h"
#include <iostream>
#include <functional>

Camera::Camera(glm::vec3 position, float yaw, float pitch)
               : Position(position), Yaw(yaw), Pitch(pitch),
               MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
{
    updateCameraVectors();
}

glm::mat4 Camera::GetViewMatrix(bool orbit) {
    if (orbit)
    {
        float x = TargetDistanceSmooth * glm::sin(glm::radians(ThetaSmooth)) * glm::sin(glm::radians(PhiSmooth));
        float z = TargetDistanceSmooth * glm::sin(glm::radians(ThetaSmooth)) * glm::cos(glm::radians(PhiSmooth));
        float y = TargetDistanceSmooth * glm::cos(glm::radians(ThetaSmooth));

        OrbitPosition = glm::vec3(x, y, z) + TargetSmooth;

        return glm::lookAt(OrbitPosition, TargetSmooth, WorldUp);
    }
    return glm::lookAt(Position, Position + Forward, Up);
}

void Camera::ProcessKeyboard(Camera_Movement direction, float deltaTime)
{
    float velocity = MovementSpeed * deltaTime;
    switch(direction)
    {
        case FORWARD:
            Position += Forward * velocity;
            break;
        case BACKWARD:
            Position -= Forward * velocity;
            break;
        case LEFT:
            Position -= Right * velocity;
            break;
        case RIGHT:
            Position += Right * velocity;
            break;
        case UP:
            Position += WorldUp * velocity;
            break;
        case DOWN:
            Position -= WorldUp * velocity;
            break;
    }
}

void Camera::ProcessMouseMovement(float xoffset, float yoffset, bool orbit, bool pan, bool constrainPitch)
{
    xoffset *= MouseSensitivity;
    yoffset *= MouseSensitivity;

    if (orbit)
    {
        if (pan)
        {
            // since target smooth is what you're actually seeing
            glm::vec3 forward = glm::normalize(TargetSmooth - OrbitPosition);
            glm::vec3 right = glm::normalize(glm::cross(forward, WorldUp));
            glm::vec3 up    = glm::normalize(glm::cross(right, forward));
            Target -= right * xoffset * 0.05f;
            Target -= up * yoffset * 0.05f;
        }
        else
        {
            // Theta is pitch and Phi is yaw
            Phi   += xoffset;
            Theta += yoffset;
        }
    }
    else
    {
        Yaw   += xoffset;
        Pitch += yoffset;
    }

    // make sure that when pitch is out of bounds, screen doesn't get flipped
    if (constrainPitch)
    {
        Theta = std::clamp(Theta, 1.0f, 179.0f);
        Pitch = std::clamp(Pitch, -89.0f, 89.0f);
    }

    // update Forward, Right and Up Vectors using the updated Euler angles
    updateCameraVectors();
}

void Camera::ProcessMouseScroll(float yoffset, bool orbit)
{
    if (orbit)
    {
        TargetDistance += yoffset * 0.2f;
        TargetDistance = std::clamp(TargetDistance, 0.5f, 100.0f);
    }
    else
    {
        float min = 1.0f;
        float max = 90.0f;

        Zoom += yoffset;
        if (Zoom < min)
            Zoom = min;
        if (Zoom > max)
            Zoom = max;
    }
}

void Camera::Update(float delta)
{
    float a = 10.0f * delta;
    ThetaSmooth = glm::mix(ThetaSmooth, Theta, a);
    PhiSmooth = glm::mix(PhiSmooth, Phi, a);
    ZoomSmooth = glm::mix(ZoomSmooth, Zoom, a);

    TargetSmooth = glm::vec3(
        TargetSmooth.x + (Target.x - TargetSmooth.x) * a,
        TargetSmooth.y + (Target.y - TargetSmooth.y) * a,
        TargetSmooth.z + (Target.z - TargetSmooth.z) * a
    );

    TargetDistanceSmooth = glm::mix(TargetDistanceSmooth, TargetDistance, a);
}

void Camera::updateCameraVectors()
{
    Forward.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    Forward.y = sin(glm::radians(Pitch));
    Forward.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    Forward = glm::normalize(Forward);
    // also re-calculate the Right and Up vector
    Right = glm::normalize(glm::cross(Forward, WorldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
    Up    = glm::normalize(glm::cross(Right, Forward));
}

void Camera::Reset(glm::vec3 position, float yaw, float pitch, float targetDistance)
{
    Yaw = yaw;
    Pitch = pitch;
    Theta = pitch + 90;
    Phi = 0;
    Zoom = 45;
    Target = position;
    TargetDistance = targetDistance;
    Position = position - TargetDistance * Forward;
    updateCameraVectors();
}
