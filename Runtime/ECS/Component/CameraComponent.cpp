#include <CameraComponent.hpp>
#include <TransformComponent.hpp>
#include <Object.hpp>

namespace Spore
{
	CameraComponent::CameraComponent()
	{
		m_name = "Camera";
		m_button_image_reset = new Texture("./Assets/Utils/Images/reset.png");
		m_camera = new Camera(0.0f, 1.0f, 0.0f);
	}

	CameraComponent::~CameraComponent()
	{

	}

	void CameraComponent::InspectorPanel()
	{
		if (ImGui::CollapsingHeader(m_name.c_str(), true))
		{
			float offset [3] = { m_x_offset, m_y_offset, m_z_offset };
			ImGui::Text("Camera");
			ImGui::PushID("Inspector::Camera::Offset");
			ImGui::DragFloat3("##Inspector::Camera::Offset", offset, 1.0f);
			ImGui::PopID();
			ImGui::SameLine();
			ImGui::PushID("Inspector::Camera::ImageButtonResetOffset");
			if (ImGui::ImageButton((ImTextureID) (intptr_t) m_button_image_reset->m_ID, ImVec2(13, 13)))
			{
			}
			if (ImGui::IsItemClicked())
			{
				offset [0] = 3.0f;
				offset [1] = 3.0f;
				offset [2] = 3.0f;
			}
			ImGui::PopID();
			m_x_offset = offset [0];
			m_y_offset = offset [1];
			m_z_offset = offset [2];
		}
	}

	void CameraComponent::Tick(float32 p_delta_time)
	{
		TransformComponent* transformComponent = dynamic_cast<TransformComponent*>(GetReferencedObject()->GetComponent("Transform"));
		if (g_tick_run && transformComponent != nullptr)
		{
			vec3f positionTemp = transformComponent->GetPosition();
			m_camera->m_position = vec3f(positionTemp.x + m_x_offset, positionTemp.y + m_y_offset, positionTemp.z + m_z_offset);
		}
	}

	void CameraComponent::SetCamera(Camera* p_camera)
	{
		m_camera = p_camera;
	}

	Camera* CameraComponent::GetCamera()
	{
		return m_camera;
	}
}