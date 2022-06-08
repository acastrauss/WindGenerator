#pragma once
#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Window/Keyboard.h"


static const GLfloat default_movement_speed = 5.0f;
static const GLfloat default_turn_speed = 0.15f;
static const GLfloat max_pitch_angle = 89.0f;
static const GLfloat max_yaw_angle = 360.0f;
static const GLfloat min_yaw_angle = 0.0f;
static const GLfloat camera_max_movement = 10.0f;


class Camera
{
private:
	
	glm::vec3 position;
	glm::vec3 up;
	glm::vec3 front;
	glm::vec3 right;
	glm::vec3 world_up;
	
	GLfloat yaw;
	GLfloat pitch;

	GLfloat movement_speed;
	GLfloat turn_speed;

	Keyboard* keyboard;

	void update();
	void moveFrontBack(GLfloat velocity);
	void moveSideToSide(GLfloat velocity);
	void moveUpDown(GLfloat velocity);


public:
	Camera(glm::vec3 initial_position, glm::vec3 world_up, GLfloat initial_yaw, GLfloat initial_pitch);
	void move(float delta_time);
	void turn(float x_change,float y_change);
	void setMovementSpeed(GLfloat movementSpeed);
	glm::vec3 GetCameraPosition() const;
	glm::mat4 calculateViewMatrix();
	~Camera();
};