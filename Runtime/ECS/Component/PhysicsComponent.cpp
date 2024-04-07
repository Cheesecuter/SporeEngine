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

	void PhysicsComponent::CreateAndAddBody()
	{
		m_body = m_body_interface->CreateBody(*m_body_creation_settings);
		m_body_interface->AddBody(m_body->GetID(), JPH::EActivation::Activate);
	}

	JPH::Body* PhysicsComponent::GetBody()
	{
		return m_body;
	}

	void PhysicsComponent::SetBodyInterface(JPH::BodyInterface* p_body_interface)
	{
		m_body_interface = p_body_interface;
	}

	void PhysicsComponent::SetPosition(const vec3f& p_potision)
	{
		m_body_interface->SetPosition(m_body->GetID(), JPHVec3(p_potision), JPH::EActivation::DontActivate);
	}

	void PhysicsComponent::SetRotation(const vec3f& p_rotation)
	{
		m_body_interface->SetRotation(m_body->GetID(), JPHQuat(quat(glm::radians(p_rotation))), JPH::EActivation::DontActivate);
	}

	void PhysicsComponent::SetTransform(const Transform p_transform)
	{
		m_transform = p_transform.GetMatrix();
	}

	vec3f PhysicsComponent::GetPosition()
	{
		m_position = Vec3f(m_body_interface->GetCenterOfMassPosition(m_body->GetID()));
		return m_position;
	}

	vec3f PhysicsComponent::GetRotation()
	{
		m_rotation = Vec3f(m_body_interface->GetRotation(m_body->GetID()));
		return m_rotation;
	}

	mat4x4f PhysicsComponent::GetTransform()
	{
		return m_transform;
	}

	vec3f PhysicsComponent::GetVelocity()
	{
		return m_velocity;
	}

	void PhysicsComponent::Tick(uint32 p_step)
	{
		/*JPH::RVec3 position = JPHVec3(m_position);
		JPH::Vec3 velocity = JPHVec3(m_velocity);*/
		m_position = Vec3f(m_body_interface->GetCenterOfMassPosition(m_body->GetID()));
		m_rotation = Vec3f(m_body_interface->GetRotation(m_body->GetID()));
		m_velocity = Vec3f(m_body_interface->GetLinearVelocity(m_body->GetID()));
		std::cout << "Step " << p_step << ": " <<
			"Position = (" << m_position.x << ", " << m_position.y << ", " << m_position.z << "), " <<
			"Rotation = (" << m_rotation.x << ", " << m_rotation.y << ", " << m_rotation.z << "), " <<
			"Velocity = (" << m_velocity.x << ", " << m_velocity.y << ", " << m_velocity.z << ")" <<
			std::endl;
	}
}