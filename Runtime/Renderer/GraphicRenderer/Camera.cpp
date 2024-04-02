#include <Camera.hpp>

namespace Spore
{
	Camera::Camera(vec3f p_position, vec3f p_up,
				   float32 p_yaw, float32 p_pitch) :
		m_front(vec3f(0.0f, 0.0f, -1.0f)),
		m_movement_speed(SPEED),
		m_mouse_sensitivity(SENSITIVITY),
		m_zoom(ZOOM)
	{
		m_position = p_position;
		m_world_up = p_up;
		m_yaw = p_yaw;
		m_pitch = p_pitch;
		UpdateCameraVectors();
	}

	Camera::Camera(float32 p_pos_x, float32 p_pos_y, float32 p_pos_z,
				   float32 p_up_x, float32 p_up_y, float32 p_up_z,
				   float32 p_yaw, float32 p_pitch) :
		m_front(vec3f(0.0f, 0.0f, -1.0f)),
		m_movement_speed(SPEED),
		m_mouse_sensitivity(SENSITIVITY),
		m_zoom(ZOOM)
	{
		m_position = vec3f(p_pos_x, p_pos_y, p_pos_z);
		m_world_up = vec3f(p_up_x, p_up_y, p_up_z);
		m_yaw = p_yaw;
		m_pitch = p_pitch;
		UpdateCameraVectors();
	}

	mat4f Camera::GetViewMatrix()
	{
		return glm::lookAt(m_position, m_position + m_front, m_up);
	}

	void Camera::ProcessKeyboard(Camera_Movement p_direction, float32 p_delta_time)
	{
		float32 velocity = m_movement_speed * p_delta_time;
		if (p_direction == FORWARD)
			m_position += m_front * velocity;
		if (p_direction == BACKWARD)
			m_position -= m_front * velocity;
		if (p_direction == LEFT)
			m_position -= m_right * velocity;
		if (p_direction == RIGHT)
			m_position += m_right * velocity;
		if (p_direction == UP)
			m_position += m_up * velocity;
		if (p_direction == DOWN)
			m_position -= m_up * velocity;
	}

	void Camera::ProcessMouseMovement(float32 p_x_offset, float32 p_y_offset, GLboolean p_constrain_pitch)
	{
		p_x_offset *= m_mouse_sensitivity;
		p_y_offset *= m_mouse_sensitivity;

		m_yaw += p_x_offset;
		m_pitch += p_y_offset;

		// make sure that when pitch is out of bounds, screen doesn't get flipped
		if (p_constrain_pitch)
		{
			if (m_pitch > 89.0f)
				m_pitch = 89.0f;
			if (m_pitch < -89.0f)
				m_pitch = -89.0f;
		}

		UpdateCameraVectors();
	}

	void Camera::ProcessMouseScroll(float32 p_y_offset)
	{
		m_zoom -= (float32) p_y_offset;
		if (m_zoom < 1.0f)
			m_zoom = 1.0f;
		if (m_zoom > 45.0f)
			m_zoom = 45.0f;
	}

	void Camera::UpdateCameraVectors()
	{
		// calculate the new Front vector
		vec3f front;
		front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
		front.y = sin(glm::radians(m_pitch));
		front.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
		m_front = glm::normalize(front);
		// also re-calculate the Right and Up vector.
		// normalize the vectors, because their length gets closer to 0 the more you
		// look up or down which results in slower movement.
		m_right = glm::normalize(glm::cross(m_front, m_world_up));
		m_up = glm::normalize(glm::cross(m_right, m_front));
	}
}