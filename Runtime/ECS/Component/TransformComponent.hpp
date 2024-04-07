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
		virtual ~TransformComponent();
		void SetPosition(const vec3f& p_position);
		void SetRotation(const vec3f& p_rotation);
		void SetScale(const vec3f& p_scale);
		vec3f GetPosition() const;
		vec3f GetRotation() const;
		vec3f GetScale() const;
		vec3f GetFront() const;
		vec3f GetRight() const;
		vec3f GetUp() const;
		mat4x4f GetMatrix() const;

	protected:
		Transform m_transform;
		Transform m_transformBuffer [2];
		uint64 m_currentIndex { 0 };
		uint64 m_nextIndex { 1 };

	private:

	};
}

#endif
