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
		void CreateAndAddBody(JPH::BodyInterface* p_body_interface);
		JPH::Body* GetBody();
		vec3f GetPosition() const;
		vec3f GetVelocity() const;
		void Tick(uint32 p_step, JPH::BodyInterface* p_body_interface);

	protected:

	private:
		JPH::Body* m_body;
		JPH::BodyCreationSettings* m_body_creation_settings;
		vec3f m_position = vec3f(0.0f, 0.0f, 0.0f);
		vec3f m_velocity = vec3f(0.0f, 0.0f, 0.0f);
	};
}