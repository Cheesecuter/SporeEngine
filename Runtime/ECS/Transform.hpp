#pragma once
#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP

#include <Types.hpp>

namespace Spore
{
	class Transform
	{
	public:
		Transform();
		Transform(const vec3f& p_position, const vec3f& p_rotation, const vec3f& p_scale);
		~Transform();

		vec3f m_front;
		vec3f m_right;
		vec3f m_up;
		vec3f m_position;
		vec3f m_rotation;
		vec3f m_scale;
		const vec3f m_world_up = vec3f(0.0f, 1.0f, 0.0f);

		void UpdateVectors();
		mat4x4f GetMatrix() const;

	protected:

	private:

	};
}

#endif
