#include <TransformComponent.hpp>

namespace Spore
{
	TransformComponent::TransformComponent()
	{
		m_name = "Transform";
	}

	void TransformComponent::SetPosition(const vec3f& p_position)
	{
		//transformBuffer [nextIndex].position = position_p;
		m_transformBuffer [m_currentIndex].m_position = p_position;
		m_transform.m_position = p_position;
		m_is_dirty = true;
	}

	void TransformComponent::SetRotation(const vec3f& p_rotation)
	{
		//transformBuffer [nextIndex].rotation = rotation_p;
		m_transformBuffer [m_currentIndex].m_rotation = p_rotation;
		m_transform.m_rotation = p_rotation;
		m_is_dirty = true;
	}

	void TransformComponent::SetScale(const vec3f& p_scale)
	{
		//transformBuffer [nextIndex].scale = scale_p;
		m_transformBuffer [m_currentIndex].m_scale = p_scale;
		m_transform.m_scale = p_scale;
		m_is_dirty = true;
		m_is_scale_dirty = true;
	}
	
	vec3f TransformComponent::GetPosition() const
	{
		return m_transformBuffer [m_currentIndex].m_position;
	}
	
	vec3f TransformComponent::GetRotation() const
	{
		return m_transformBuffer [m_currentIndex].m_rotation;
	}
	
	vec3f TransformComponent::GetScale() const
	{
		return m_transformBuffer [m_currentIndex].m_scale;
	}

	vec3f TransformComponent::GetFront() const
	{
		return m_transformBuffer [m_currentIndex].m_front;
	}

	vec3f TransformComponent::GetRight() const
	{
		return m_transformBuffer [m_currentIndex].m_right;
	}

	vec3f TransformComponent::GetUp() const
	{
		return m_transformBuffer [m_currentIndex].m_up;
	}

	mat4x4f TransformComponent::GetMatrix() const
	{
		return m_transform.GetMatrix();
	}
}
