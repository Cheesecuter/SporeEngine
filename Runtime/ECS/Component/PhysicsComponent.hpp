#pragma once

#include <Types.hpp>
#include <Component.hpp>
#include <Transform.hpp>
#include <PhysicSyetemHeaders.h>
#include <Layers.hpp>

namespace Spore
{
	class PhysicsComponent : public Component
	{
	public:
		PhysicsComponent();
		virtual ~PhysicsComponent();
		void SetBodyCreationSettings(const JPH::Shape* p_shape, JPH::RVec3 p_position, JPH::Quat p_rotation,
									 JPH::EMotionType p_motion_type, JPH::ObjectLayer p_object_layer);
		void CreateAndAddBody();
		JPH::Body* GetBody();
		void SetBodyInterface(JPH::BodyInterface* p_body_interface);
		void SetPosition(const vec3f& p_potision);
		void SetRotation(const vec3f& p_rotation);
		//void SetScale(const vec3f& p_scale);
		void SetTransform(const Transform p_transform);
		vec3f GetPosition();
		vec3f GetRotation();
		//vec3f GetScale();
		mat4x4f GetTransform();
		vec3f GetVelocity();

		void Tick(uint32 p_step);

	protected:

	private:
		JPH::Body* m_body;
		JPH::BodyCreationSettings* m_body_creation_settings;
		JPH::BodyInterface* m_body_interface = nullptr;
		mat4x4f m_transform;
		vec3f m_position = vec3f(0.0f, 0.0f, 0.0f);
		vec3f m_rotation = vec3f(0.0f, 0.0f, 0.0f);
		vec3f m_scale = vec3f(1.0f, 1.0f, 1.0f);
		vec3f m_velocity = vec3f(0.0f, 0.0f, 0.0f);
	};
}