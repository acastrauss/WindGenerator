#include "Camera.h"
#include <cmath>
#include <tuple>


Camera::Camera(glm::vec3 initial_position, glm::vec3 world_up, GLfloat initial_yaw, GLfloat initial_pitch)
{
    this->position = initial_position;
    this->world_up = world_up;
    this->yaw = initial_yaw;
    this->pitch = initial_pitch;
    this->front = glm::vec3(0.0f, 0.0f, -1.0f);

    this->movement_speed = default_movement_speed;
    this->turn_speed = default_turn_speed;

    keyboard = Keyboard::getInstance();

    update();
}

void Camera::setMovementSpeed(GLfloat movementSpeed)
{
    this->movement_speed = movementSpeed;
}

Camera::~Camera(){}

void Camera::moveFrontBack(GLfloat velocity)
{
    if (keyboard->checkKeySet(GLFW_KEY_W))
    {
        position += front * velocity;
    }

    if (keyboard->checkKeySet(GLFW_KEY_S))
    {
        position -= front * velocity;
    }
}


void Camera::moveUpDown(GLfloat velocity)
{

    if (keyboard->checkKeySet(GLFW_KEY_UP))
    {
        position += up * velocity;
    }

    if (keyboard->checkKeySet(GLFW_KEY_DOWN))
    {
        position -= up * velocity;
    }

}

void Camera::moveSideToSide(GLfloat velocity)
{

    if (keyboard->checkKeySet(GLFW_KEY_A))
    {
        position -= right * velocity;
    }

    if (keyboard->checkKeySet(GLFW_KEY_D))
    {
        position += right * velocity;
    }

}


void Camera::move(float delta_time)
{
    GLfloat velocity = movement_speed * delta_time;

    moveFrontBack(velocity); 
    moveSideToSide(velocity);
    moveUpDown(velocity);

    if (position.y < 7.0f)
        position.y = 7.0f;
}

void Camera::turn(float x_change,float y_change)
{
    x_change   = (x_change * turn_speed);
    y_change    = (y_change * turn_speed);


    // Ogranicava pomeraj kamere, trebalo bi uraditi mouse picking
    // Ali ovo zadovoljava 
    if (std::abs(x_change) <= camera_max_movement)
    {
        yaw += x_change;
    }

    if (std::abs(y_change) <= camera_max_movement)
    {
        pitch += y_change;
    }

    if (pitch > max_pitch_angle)
    {
        pitch = max_pitch_angle;
    }
    else if (pitch < -max_pitch_angle)
    {
        pitch = -max_pitch_angle;
    }


    if (yaw > max_yaw_angle)
        yaw = min_yaw_angle;
    else if (yaw < min_yaw_angle)
        yaw = max_yaw_angle;

    update();
}


void Camera::update()
{
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

    front = glm::normalize(front);

    right = glm::normalize(glm::cross(front, world_up));
    up = glm::normalize(glm::cross(right, front));


}

glm::mat4 Camera::calculateViewMatrix()
{
    return glm::lookAt(position, position + front, up);
}

glm::vec3 Camera::GetCameraPosition() const
{
    return position;
}