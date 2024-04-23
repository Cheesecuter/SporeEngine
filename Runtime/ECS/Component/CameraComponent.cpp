#include <CameraComponent.hpp>

namespace Spore
{
	CameraComponent::CameraComponent()
	{
		m_name = "Camera";
	}

	CameraComponent::~CameraComponent()
	{

	}

	void CameraComponent::InspectorPanel()
	{
		if (ImGui::CollapsingHeader(m_name.c_str(), true))
		{
			ImGui::Text("Camera");
		}
	}

	void CameraComponent::Tick(float32 p_delta_time)
	{

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