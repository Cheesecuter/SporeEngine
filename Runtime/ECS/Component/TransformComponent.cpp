#include <TransformComponent.hpp>

namespace Spore
{
	TransformComponent::TransformComponent()
	{
		name = "Transform";
	}

	void TransformComponent::SetPosition(const vec3f& position_p)
	{
		//transformBuffer [nextIndex].position = position_p;
		transformBuffer [currentIndex].position = position_p;
		transform.position = position_p;
		isDirty = true;
	}

	void TransformComponent::SetRotation(const vec3f& rotation_p)
	{
		//transformBuffer [nextIndex].rotation = rotation_p;
		transformBuffer [currentIndex].rotation = rotation_p;
		transform.rotation = rotation_p;
		isDirty = true;
	}

	void TransformComponent::SetScale(const vec3f& scale_p)
	{
		//transformBuffer [nextIndex].scale = scale_p;
		transformBuffer [currentIndex].scale = scale_p;
		transform.scale = scale_p;
		isDirty = true;
		isScaleDirty = true;
	}
	
	vec3f TransformComponent::GetPosition() const
	{
		return transformBuffer [currentIndex].position;
	}
	
	vec3f TransformComponent::GetRotation() const
	{
		return transformBuffer [currentIndex].rotation;
	}
	
	vec3f TransformComponent::GetScale() const
	{
		return transformBuffer [currentIndex].scale;
	}

	mat4x4f TransformComponent::GetMatrix() const
	{
		return transform.GetMatrix();
	}
}
