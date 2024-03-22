#pragma once
#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <Types.hpp>

namespace Spore
{
	// Defines several possible options for camera movement.
		// Used as abstraction to stay away from window-system specific input methods.
	enum Camera_Movement
	{
		FORWARD = 0,
		BACKWARD = 1,
		LEFT = 2,
		RIGHT = 3,
		UP = 4,
		DOWN = 5
	};

	// Default camera values.
	const float32 YAW = -90.0f;
	const float32 PITCH = 0.0f;
	const float32 SPEED = 2.5f;
	const float32 SENSITIVITY = 0.1f;
	const float32 ZOOM = 45.0f;

	// An abstract camera class that processes input and calculates the corresponding Euler Angles, Vectors
	// and Matrices for use in OpenGL.
	class Camera
	{
	public:
		// camera attributes
		vec3f Position;
		vec3f Front;
		vec3f Up;
		vec3f Right;
		vec3f WorldUp;
		// euler angles
		float32 Yaw;
		float32 Pitch;
		// camera options
		float32 MovementSpeed;
		float32 MouseSensitivity;
		float32 Zoom;

		// constructor with vectors
		Camera(vec3f position_p = vec3f(0.0f, 0.0f, 0.0f),
			   vec3f up_p = vec3f(0.0f, 1.0f, 0.0f),
			   float32 yaw_p = YAW, float32 pitch_p = PITCH);

		// constructor with scalar values
		Camera(float32 posX_p, float32 posY_p, float32 posZ_p,
			   float32 upX_p, float32 upY_p, float32 upZ_p,
			   float32 yaw_p, float32 pitch_p);

		// Return the view matrix calculated using Euler Angles and the LookAt Matrix.
		mat4f GetViewMatrix();

		// Processes input received from any keyboard-like input system.
		// Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems).
		void ProcessKeyboard(Camera_Movement direction_p, float32 deltaTime_p);

		// Processes input received from a mouse input system.
		// Excepts the offset value in both the x and y direction.
		void ProcessMouseMovement(float32 xOffset_p, float32 yOffset_p, GLboolean constrainPitch_p = true);

		// Processes input received from a mouse scroll-wheel event.
		// Only requires input in the vertical wheel-axis.
		void ProcessMouseScroll(float32 yOffset_p);

	protected:

	private:
		// Calculates the front vector from the Camera's (updated) Euler Angles.
		void UpdateCameraVectors();
	};
}

#endif
