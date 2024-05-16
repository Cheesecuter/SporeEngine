#pragma once

#include <Types.hpp>

namespace Spore
{
	class Transform
	{
	public:
		Transform();
		Transform(const vec3f& p_position, const vec3f& p_rotation, const vec3f& p_scale);
		~Transform();

	public:
		vec3f m_front;
		vec3f m_right;
		vec3f m_up;
		vec3f m_position;
		vec3f m_rotation;
		vec3f m_scale;
		const vec3f m_world_up = vec3f(0.0f, 1.0f, 0.0f);

	protected:

	private:

	public:
		/**
		 * @brief Update the transformation vectors.
		 *
		 * This function updates the front, up, and right vectors of the transformation based on the current rotation.
		 */
		void UpdateVectors();
		/**
		 * @brief Get the transformation matrix.
		 *
		 * This function calculates and returns the transformation matrix representing the current transformation.
		 *
		 * @return Transformation matrix representing the current transformation.
		 */
		mat4x4f GetMatrix() const;

	protected:

	private:

	};
}
