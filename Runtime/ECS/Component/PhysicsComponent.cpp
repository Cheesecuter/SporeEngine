#include <PhysicsComponent.hpp>
#include <TransformComponent.hpp>
#include <Object.hpp>

namespace Spore
{
	PhysicsComponent::PhysicsComponent()
	{
		m_name = "Physics";
		m_button_image_reset = new Texture("./Assets/Utils/Images/reset.png");
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

			SetLinearVelocity(Vec3f(m_body->GetMotionProperties()->GetLinearVelocity()));
			float linearVelocity [3] = { m_linear_velocity.x, m_linear_velocity.y, m_linear_velocity.z };
			ImGui::Text("Linear Velocity");
			ImGui::PushID("Inspector::Physics::EMotionProperties::Linear_Velocity");
			ImGui::DragFloat3("##Inspector::Physics::EMotionProperties::Linear_Velocity", linearVelocity, 0.1f);
			ImGui::PopID();
			ImGui::SameLine();
			ImGui::PushID("Inspector::Physics::ImageButtonResetLinear_Velocity");
			if (ImGui::ImageButton((ImTextureID) (intptr_t) m_button_image_reset->m_ID, ImVec2(13, 13)))
			{
			}
			if (ImGui::IsItemClicked())
			{
				linearVelocity [0] = 0.0f;
				linearVelocity [1] = 0.0f;
				linearVelocity [2] = 0.0f;
			}
			ImGui::PopID();
			m_body->GetMotionProperties()->SetLinearVelocity(JPHVec3(vec3f(linearVelocity [0], linearVelocity [1], linearVelocity [2])));

			SetAngularVelocity(Vec3f(m_body->GetMotionProperties()->GetAngularVelocity()));
			float angularVelocity [3] = { m_angular_velocity.x, m_angular_velocity.y, m_angular_velocity.z };
			ImGui::Text("Angular Velocity");
			ImGui::PushID("Inspector::Physics::EMotionProperties::Angular_Velocity");
			ImGui::DragFloat3("##Inspector::Physics::EMotionProperties::Angular_Velocity", angularVelocity, 0.1f);
			ImGui::PopID();
			ImGui::SameLine();
			ImGui::PushID("Inspector::Physics::ImageButtonResetAngular_Velocity");
			if (ImGui::ImageButton((ImTextureID) (intptr_t) m_button_image_reset->m_ID, ImVec2(13, 13)))
			{
			}
			if (ImGui::IsItemClicked())
			{
				angularVelocity [0] = 0.0f;
				angularVelocity [1] = 0.0f;
				angularVelocity [2] = 0.0f;
			}
			ImGui::PopID();
			m_body->GetMotionProperties()->SetAngularVelocity(JPHVec3(vec3f(angularVelocity [0], angularVelocity [1], angularVelocity [2])));

			SetGravityFactor(m_body->GetMotionProperties()->GetGravityFactor());
			ImGui::Text("GravityFactor");
			ImGui::DragFloat("##Inspector::Physics::EMotionProperties::GravityFactor", &m_gravity_factor, 0.1f);
			m_body->GetMotionProperties()->SetGravityFactor(m_gravity_factor);

			SetRestitution(m_body->GetRestitution());
			ImGui::Text("Restitution");
			ImGui::DragFloat("##Inspector::Physics::BodySettings::Restitution", &m_restitution, 0.1f);
			m_body->SetRestitution(m_restitution);
			
			SetFriction(m_body->GetFriction());
			ImGui::Text("Friction");
			ImGui::DragFloat("##Inspector::Physics::BodySettings::Friction", &m_friction, 0.1f);
			m_body->SetFriction(m_friction);
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

	void PhysicsComponent::SetLinearVelocity(vec3f p_velocity)
	{
		m_linear_velocity = p_velocity;
	}

	void PhysicsComponent::SetLinearVelocity(float32 p_x, float32 p_y, float32 p_z)
	{
		m_linear_velocity = vec3f(p_x, p_y, p_z);
	}

	vec3f PhysicsComponent::GetLinearVelocity()
	{
		return m_linear_velocity;
	}

	void PhysicsComponent::SetAngularVelocity(vec3f p_velocity)
	{
		m_angular_velocity = p_velocity;
	}

	void PhysicsComponent::SetAngularVelocity(float32 p_x, float32 p_y, float32 p_z)
	{
		m_angular_velocity = vec3f(p_x, p_y, p_z);
	}

	vec3f PhysicsComponent::GetAngularVelocity()
	{
		return m_angular_velocity;
	}

	void PhysicsComponent::SetGravityFactor(float32 p_gravity_factor)
	{
		m_gravity_factor = p_gravity_factor;
	}

	float32 PhysicsComponent::GetGravityFactor()
	{
		return m_gravity_factor;
	}

	void PhysicsComponent::SetRestitution(float32 p_restitution)
	{
		m_restitution = p_restitution;
	}

	float32 PhysicsComponent::GetRestitution()
	{
		return m_restitution;
	}

	void PhysicsComponent::SetFriction(float32 p_friction)
	{
		m_friction = p_friction;
	}

	float32 PhysicsComponent::GetFriction()
	{
		return m_friction;
	}

	vec3f PhysicsComponent::GetVelocity()
	{
		return m_velocity;
	}
}