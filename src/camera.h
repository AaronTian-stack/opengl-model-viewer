#ifndef OPENGL_MODEL_VIEWER_CAMERA_H
#define OPENGL_MODEL_VIEWER_CAMERA_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods
enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    UP,
    DOWN
};

const float YAW         = -90.0f;
const float PITCH       =  0.0f;
const float SPEED       =  2.0f;
const float SENSITIVITY =  0.05f;
const float ZOOM        =  45.0f;

class Camera {
    public:
        // camera Attributes
        glm::vec3 Position, OrbitPosition;
        glm::vec3 Forward = glm::vec3(0.0f, 0.0f, -1.0f);
        glm::vec3 Up;
        glm::vec3 Right;
        glm::vec3 WorldUp = glm::vec3(0.0f, 1.0f, 0.0f);

        glm::vec3 Target;
        glm::vec3 TargetSmooth;
        float TargetDistance = 5.0f;
        float TargetDistanceSmooth = TargetDistance;

        // euler Angles
        float Yaw;
        float Pitch;

        float Theta = 90;
        float Phi;

        // camera options
        float MovementSpeed;
        float MouseSensitivity;
        float Zoom;
        float ZoomSmooth;

        Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
               float yaw = YAW, float pitch = PITCH);

        glm::mat4 GetViewMatrix(bool orbit);

        void ProcessKeyboard(Camera_Movement direction, float deltaTime);

        void ProcessMouseMovement(float xoffset, float yoffset, bool orbit = false, bool pan = false, bool constrainPitch = true);

        void ProcessMouseScroll(float yoffset, bool orbit = false);

        // updates the orbital smoothed values
        void Update(float delta);

        void Reset(glm::vec3 position, float yaw = -90, float pitch = 0, float targetDistance = 5);

    private:
        float ThetaSmooth = Theta;
        float PhiSmooth = Phi;

        void updateCameraVectors();
};

#endif
