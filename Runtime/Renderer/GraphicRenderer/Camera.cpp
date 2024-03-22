#include <Camera.hpp>

namespace Spore
{
	Camera::Camera(vec3f position_p, vec3f up_p,
				   float32 yaw_p, float32 pitch_p) :
		Front(vec3f(0.0f, 0.0f, -1.0f)),
		MovementSpeed(SPEED),
		MouseSensitivity(SENSITIVITY),
		Zoom(ZOOM)
	{
		Position = position_p;
		WorldUp = up_p;
		Yaw = yaw_p;
		Pitch = pitch_p;
		UpdateCameraVectors();
	}

	Camera::Camera(float32 posX_p, float32 posY_p, float32 posZ_p,
				   float32 upX_p, float32 upY_p, float32 upZ_p,
				   float32 yaw_p, float32 pitch_p) :
		Front(vec3f(0.0f, 0.0f, -1.0f)),
		MovementSpeed(SPEED),
		MouseSensitivity(SENSITIVITY),
		Zoom(ZOOM)
	{
		Position = vec3f(posX_p, posY_p, posZ_p);
		WorldUp = vec3f(upX_p, upY_p, upZ_p);
		Yaw = yaw_p;
		Pitch = pitch_p;
		UpdateCameraVectors();
	}

	mat4f Camera::GetViewMatrix()
	{
		return glm::lookAt(Position, Position + Front, Up);
	}

	void Camera::ProcessKeyboard(Camera_Movement direction_p, float32 deltaTime_p)
	{
		float32 velocity = MovementSpeed * deltaTime_p;
		if (direction_p == FORWARD)
			Position += Front * velocity;
		if (direction_p == BACKWARD)
			Position -= Front * velocity;
		if (direction_p == LEFT)
			Position -= Right * velocity;
		if (direction_p == RIGHT)
			Position += Right * velocity;
		if (direction_p == UP)
			Position += Up * velocity;
		if (direction_p == DOWN)
			Position -= Up * velocity;
	}

	void Camera::ProcessMouseMovement(float32 xOffset_p, float32 yOffset_p, GLboolean constrainPitch_p)
	{
		xOffset_p *= MouseSensitivity;
		yOffset_p *= MouseSensitivity;

		Yaw += xOffset_p;
		Pitch += yOffset_p;

		// make sure that when pitch is out of bounds, screen doesn't get flipped
		if (constrainPitch_p)
		{
			if (Pitch > 89.0f)
				Pitch = 89.0f;
			if (Pitch < -89.0f)
				Pitch = -89.0f;
		}

		UpdateCameraVectors();
	}

	void Camera::ProcessMouseScroll(float32 yOffset_p)
	{
		Zoom -= (float32) yOffset_p;
		if (Zoom < 1.0f)
			Zoom = 1.0f;
		if (Zoom > 45.0f)
			Zoom = 45.0f;
	}

	void Camera::UpdateCameraVectors()
	{
		// calculate the new Front vector
		vec3f front;
		front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
		front.y = sin(glm::radians(Pitch));
		front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
		Front = glm::normalize(front);
		// also re-calculate the Right and Up vector.
		// normalize the vectors, because their length gets closer to 0 the more you
		// look up or down which results in slower movement.
		Right = glm::normalize(glm::cross(Front, WorldUp));
		Up = glm::normalize(glm::cross(Right, Front));
	}
}