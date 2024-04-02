#include <Transform.hpp>

namespace Spore
{
	Transform::Transform()
	{
		m_position = vec3f(0.0f, 0.0f, 0.0f);
		m_rotation = vec3f(0.0f, 0.0f, 0.0f);
		m_scale = vec3f(1.0f, 1.0f, 1.0f);
		UpdateVectors();
	}

	Transform::Transform(const vec3f& p_position, const vec3f& p_rotation, const vec3f& p_scale) :
		m_position(p_position), m_rotation(p_rotation), m_scale(p_scale)
	{

	}

	Transform::~Transform()
	{

	}

	void Transform::UpdateVectors()
	{
		vec4f front_temp(0.0f, 0.0f, 1.0f, 0.0f);
		vec4f up_temp(0.0f, 1.0f, 0.0f, 0.0f);
		quat quat(glm::radians(m_rotation));
		mat4x4f rot = glm::mat4_cast(quat);
		m_front = rot * front_temp;
		m_up = rot * up_temp;
		m_right = glm::normalize(glm::cross(m_front, m_up));
	}

	mat4x4f Transform::GetMatrix() const
	{
		mat4x4f mat(1.0f);
		mat4x4f scale = glm::scale(mat, m_scale);
		quat quat(glm::radians(m_rotation));
		mat4x4f rotation = glm::mat4_cast(quat);
		mat4x4f translation = glm::translate(mat, m_position);
		return translation * rotation * scale;
	}
}