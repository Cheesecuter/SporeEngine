#include <TransformComponent.hpp>
#include <PhysicsComponent.hpp>
#include <Object.hpp>

namespace Spore
{
	TransformComponent::TransformComponent()
	{
		m_name = "Transform";
		m_button_image_reset = new Texture("./Assets/Utils/Images/reset.png");
	}

	TransformComponent::~TransformComponent()
	{

	}

	void TransformComponent::InspectorPanel()
	{
		if (ImGui::CollapsingHeader(m_name.c_str(), true))
		{
			vec3f positionTemp = GetPosition();
			float position [3] = { positionTemp.x, positionTemp.y, positionTemp.z };
			ImGui::Text("Position");
			ImGui::PushID("Inspector::Transform::Position");
			ImGui::DragFloat3("##Inspector::Transform::Position", position, 0.1f);
			ImGui::PopID();
			ImGui::SameLine();
			ImGui::PushID("Inspector::Transform::ImageButtonResetPosition");
			if (ImGui::ImageButton((ImTextureID) (intptr_t) m_button_image_reset->m_ID, ImVec2(13, 13)))
			{
			}
			if (ImGui::IsItemClicked())
			{
				position [0] = 0.0f;
				position [1] = 0.0f;
				position [2] = 0.0f;
			}
			ImGui::PopID();
			SetPosition(vec3f(position [0], position [1], position [2]));

			vec3f rotationTemp = GetRotation();
			float rotation [3] = { rotationTemp.x, rotationTemp.y, rotationTemp.z };
			ImGui::Text("Rotation");
			ImGui::PushID("Inspector::Transform::Rotation");
			ImGui::DragFloat3("##Inspector::Transform::Rotation", rotation, 0.1f);
			ImGui::PopID();
			ImGui::SameLine();
			ImGui::PushID("Inspector::Transform::ImageButtonResetRotation");
			if (ImGui::ImageButton((ImTextureID) (intptr_t) m_button_image_reset->m_ID, ImVec2(13, 13)))
			{
			}
			if (ImGui::IsItemClicked())
			{
				rotation [0] = 0.0f;
				rotation [1] = 0.0f;
				rotation [2] = 0.0f;
			}
			ImGui::PopID();
			SetRotation(vec3f(rotation [0], rotation [1], rotation [2]));

			vec3f scaleTemp = GetScale();
			float scale [3] = { scaleTemp.x, scaleTemp.y, scaleTemp.z };
			ImGui::Text("Scale");
			ImGui::PushID("Inspector::Transform::Scale");
			ImGui::DragFloat3("##Inspector::Transform::Scale", scale, 0.1f);
			ImGui::PopID();
			ImGui::SameLine();
			ImGui::PushID("Inspector::Transform::ImageButtonResetScale");
			if (ImGui::ImageButton((ImTextureID) (intptr_t) m_button_image_reset->m_ID, ImVec2(13, 13)))
			{
			}
			if (ImGui::IsItemClicked())
			{
				scale [0] = 1.0f;
				scale [1] = 1.0f;
				scale [2] = 1.0f;
			}
			ImGui::PopID();
			SetScale(vec3f(scale [0], scale [1], scale [2]));
		}
	}

	void TransformComponent::Tick(float32 p_delta_time)
	{
		PhysicsComponent* physicsComponent = dynamic_cast<PhysicsComponent*>(GetReferencedObject()->GetComponent("Physics"));
		if (g_tick_run && physicsComponent != nullptr)
		{
			SetPosition(physicsComponent->GetPosition());
			SetRotation(physicsComponent->GetRotation());
		}
	}

	void TransformComponent::SetPosition(const vec3f& p_position)
	{
		//transformBuffer [nextIndex].position = position_p;
		m_transformBuffer [m_currentIndex].m_position = p_position;
		m_transform.m_position = p_position;
		m_is_dirty = true;
	}

	void TransformComponent::SetRotation(const vec3f& p_rotation)
	{
		//transformBuffer [nextIndex].rotation = rotation_p;
		m_transformBuffer [m_currentIndex].m_rotation = p_rotation;
		m_transform.m_rotation = p_rotation;
		m_is_dirty = true;
	}

	void TransformComponent::SetScale(const vec3f& p_scale)
	{
		//transformBuffer [nextIndex].scale = scale_p;
		m_transformBuffer [m_currentIndex].m_scale = p_scale;
		m_transform.m_scale = p_scale;
		m_is_dirty = true;
		m_is_scale_dirty = true;
	}
	
	vec3f TransformComponent::GetPosition() const
	{
		return m_transformBuffer [m_currentIndex].m_position;
	}
	
	vec3f TransformComponent::GetRotation() const
	{
		return m_transformBuffer [m_currentIndex].m_rotation;
	}
	
	vec3f TransformComponent::GetScale() const
	{
		return m_transformBuffer [m_currentIndex].m_scale;
	}

	vec3f TransformComponent::GetFront() const
	{
		return m_transformBuffer [m_currentIndex].m_front;
	}

	vec3f TransformComponent::GetRight() const
	{
		return m_transformBuffer [m_currentIndex].m_right;
	}

	vec3f TransformComponent::GetUp() const
	{
		return m_transformBuffer [m_currentIndex].m_up;
	}

	mat4x4f TransformComponent::GetMatrix() const
	{
		return m_transform.GetMatrix();
	}
}
