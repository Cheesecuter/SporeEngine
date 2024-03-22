#pragma once
#ifndef TRANSFORM_COMPONENT_HPP
#define TRANSFORM_COMPONENT_HPP

#include <Types.hpp>
#include <Component.hpp>
#include <Transform.hpp>

namespace Spore
{
	class TransformComponent : public Component
	{
	public:
		TransformComponent();
		void SetPosition(const vec3f& position_p);
		void SetRotation(const vec3f& rotation_p);
		void SetScale(const vec3f& scale_p);
		vec3f GetPosition() const;
		vec3f GetRotation() const;
		vec3f GetScale() const;
		mat4x4f GetMatrix() const;

	protected:
		Transform transform;
		Transform transformBuffer [2];
		uint64 currentIndex { 0 };
		uint64 nextIndex { 1 };

	private:

	};
}

#endif
