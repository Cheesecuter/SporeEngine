#include <PhysicsComponent.hpp>
#include <TransformComponent.hpp>
#include <Object.hpp>

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

	void PhysicsComponent::InspectorPanel()
	{
		if (ImGui::CollapsingHeader(m_name.c_str(), true))
		{
			ImGui::Text("Physics Component UI");
			const char* EMotionTypesIndexs [] = {
				"Dynamic",
				"Kinematic",
				"Static"
			};
			JPH::EMotionType EMotionTypes [] = {
				JPH::EMotionType::Dynamic,
				JPH::EMotionType::Kinematic,
				JPH::EMotionType::Static
			};
			static int currentEMotionTypeIndex = 0;
			JPH::EMotionType currentEMotionType = m_body_interface->GetMotionType(m_body->GetID());
			if (currentEMotionType == EMotionTypes [0])
			{
				currentEMotionTypeIndex = 0;
			}
			else if (currentEMotionType == EMotionTypes [1])
			{
				currentEMotionTypeIndex = 1;
			}
			else if (currentEMotionType == EMotionTypes [2])
			{
				currentEMotionTypeIndex = 2;
			}
			if (ImGui::BeginCombo("##Inspector::Physics::EMotionType", EMotionTypesIndexs [currentEMotionTypeIndex]))
			{
				for (uint32 i = 0; i < IM_ARRAYSIZE(EMotionTypesIndexs); i++)
				{
					const bool isSelected = (currentEMotionTypeIndex == i);
					if (ImGui::Selectable(EMotionTypesIndexs [i], isSelected))
					{
						currentEMotionTypeIndex = i;
						JPH::EActivation isActive = JPH::EActivation::DontActivate;
						if (m_body_interface->IsActive(m_body->GetID()))
						{
							isActive = JPH::EActivation::Activate;
						}
						m_body_interface->SetMotionType(m_body->GetID(), EMotionTypes[i], isActive);
					}
					if (isSelected)
					{
						ImGui::SetItemDefaultFocus();
					}
				}
				ImGui::EndCombo();
			}
			
		}
	}

	void PhysicsComponent::Tick(float32 p_delta_time)
	{
		TransformComponent* transformComponent = dynamic_cast<TransformComponent*>(GetReferencedObject()->GetComponent("Transform"));
		if (g_tick_stop && transformComponent != nullptr)
		{
			SetPosition(transformComponent->GetPosition());
			SetRotation(transformComponent->GetRotation());

			m_position = Vec3f(m_body_interface->GetCenterOfMassPosition(m_body->GetID()));
			m_rotation = Vec3f(m_body_interface->GetRotation(m_body->GetID()));
			m_velocity = Vec3f(m_body_interface->GetLinearVelocity(m_body->GetID()));
			/*std::cout << "Step " << p_delta_time << ": " <<
			"Position = (" << m_position.x << ", " << m_position.y << ", " << m_position.z << "), " <<
			"Rotation = (" << m_rotation.x << ", " << m_rotation.y << ", " << m_rotation.z << "), " <<
			"Velocity = (" << m_velocity.x << ", " << m_velocity.y << ", " << m_velocity.z << ")" <<
			std::endl;*/
		}
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

	JPH::BodyInterface* PhysicsComponent::GetBodyInterface()
	{
		return m_body_interface;
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

	void PhysicsComponent::Tick1(uint32 p_step)
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