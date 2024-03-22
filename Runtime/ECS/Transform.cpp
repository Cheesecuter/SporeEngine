#include <Transform.hpp>

namespace Spore
{
	Transform::Transform()
	{
		position = vec3f(0.0f, 0.0f, 0.0f);
		rotation = vec3f(0.0f, 0.0f, 0.0f);
		scale = vec3f(1.0f, 1.0f, 1.0f);
		UpdateVectors();
	}

	Transform::Transform(const vec3f& position_p, const vec3f& rotation_p, const vec3f& scale_p) :
		position(position_p), rotation(rotation_p), scale(scale_p)
	{

	}

	Transform::~Transform()
	{

	}

	void Transform::UpdateVectors()
	{
		vec4f frontTmp(0.0f, 0.0f, 1.0f, 0.0f);
		vec4f upTmp(0.0f, 1.0f, 0.0f, 0.0f);
		quat quat(glm::radians(rotation));
		mat4x4f rot = glm::mat4_cast(quat);
		front = rot * frontTmp;
		up = rot * upTmp;
		right = glm::normalize(glm::cross(front, up));
	}

	mat4x4f Transform::GetMatrix() const
	{
		mat4x4f mat(1.0f);
		mat4x4f s = glm::scale(mat, scale);
		quat quat(glm::radians(rotation));
		mat4x4f r = glm::mat4_cast(quat);
		mat4x4f t = glm::translate(mat, position);
		return t * r * s;
	}
}