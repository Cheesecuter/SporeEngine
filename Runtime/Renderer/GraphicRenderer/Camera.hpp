#pragma once

#include <Types.hpp>

namespace Spore
{
	enum Camera_Movement
	{
		FORWARD = 0,
		BACKWARD = 1,
		LEFT = 2,
		RIGHT = 3,
		UP = 4,
		DOWN = 5
	};

	const float32 YAW = -90.0f;
	const float32 PITCH = 0.0f;
	const float32 SPEED = 2.5f;
	const float32 SENSITIVITY = 0.1f;
	const float32 ZOOM = 45.0f;

	class Camera
	{
	public:
		// camera attributes
		vec3f m_position;
		vec3f m_front;
		vec3f m_up;
		vec3f m_right;
		vec3f m_world_up;
		// euler angles
		float32 m_yaw;
		float32 m_pitch;
		// camera options
		float32 m_movement_speed;
		float32 m_mouse_sensitivity;
		float32 m_zoom;

		Camera(vec3f p_position = vec3f(0.0f, 0.0f, 0.0f),
			   vec3f p_up = vec3f(0.0f, 1.0f, 0.0f),
			   float32 p_yaw = YAW, float32 p_pitch = PITCH);

		Camera(float32 p_pos_x, float32 p_pos_y, float32 p_pos_z,
			   float32 p_up_x, float32 p_up_y, float32 p_up_z,
			   float32 p_yaw, float32 p_pitch);

		mat4f GetViewMatrix();

		void ProcessKeyboard(Camera_Movement p_direction, float32 p_delta_time);

		void ProcessMouseMovement(float32 p_x_offset, float32 p_y_offset, GLboolean p_constrain_pitch = true);

		void ProcessMouseScroll(float32 p_y_offset);

	protected:

	private:
		void UpdateCameraVectors();
	};
}
