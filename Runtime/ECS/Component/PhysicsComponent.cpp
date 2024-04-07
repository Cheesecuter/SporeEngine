#include <PhysicsComponent.hpp>

namespace Spore
{
	PhysicsComponent::PhysicsComponent()
	{
		m_name = "Physics";
	}

	PhysicsComponent::~PhysicsComponent()
	{
		delete m_body;
	}

	void PhysicsComponent::SetBodyCreationSettings(const JPH::Shape* p_shape,
												   JPH::RVec3 p_position,
												   JPH::Quat p_rotation,
												   JPH::EMotionType p_motion_type,
												   JPH::ObjectLayer p_object_layer)
	{
		m_body_creation_settings = new JPH::BodyCreationSettings(
			p_shape, p_position, p_rotation, p_motion_type, p_object_layer);
	}

	void PhysicsComponent::CreateAndAddBody(JPH::BodyInterface* p_body_interface)
	{
		m_body = p_body_interface->CreateBody(*m_body_creation_settings);
		p_body_interface->AddBody(m_body->GetID(), JPH::EActivation::Activate);
	}

	JPH::Body* PhysicsComponent::GetBody()
	{
		return m_body;
	}

	vec3f PhysicsComponent::GetPosition() const
	{
		return m_position;
	}

	vec3f PhysicsComponent::GetVelocity() const
	{
		return m_velocity;
	}

	void PhysicsComponent::Tick(uint32 p_step, JPH::BodyInterface* p_body_interface)
	{
		/*JPH::RVec3 position = JPHVec3(m_position);
		JPH::Vec3 velocity = JPHVec3(m_velocity);*/
		m_position = Vec3f(p_body_interface->GetCenterOfMassPosition(m_body->GetID()));
		m_velocity = Vec3f(p_body_interface->GetLinearVelocity(m_body->GetID()));
		std::cout << "Step " << p_step << ": " <<
			"Position = (" << m_position.x << ", " << m_position.y << ", " << m_position.z << "), " <<
			"Velocity = (" << m_velocity.x << ", " << m_velocity.y << ", " << m_velocity.z << ")" <<
			std::endl;
	}
}