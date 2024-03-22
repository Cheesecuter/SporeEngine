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
		Transform(const vec3f& position_p, const vec3f& rotation_p, const vec3f& scale_p);
		~Transform();

		vec3f front;
		vec3f right;
		vec3f up;
		vec3f position;
		vec3f rotation;
		vec3f scale;
		const vec3f worldUp = vec3f(0.0f, 1.0f, 0.0f);

		void UpdateVectors();
		mat4x4f GetMatrix() const;

	protected:

	private:

	};
}

#endif
