#include <IDComponent.hpp>

namespace Spore
{
	IDComponent::IDComponent()
	{
		m_name = "UUID";
	}

	IDComponent::~IDComponent()
	{

	}

	void IDComponent::InspectorPanel()
	{
		if (ImGui::CollapsingHeader(m_name.c_str(), true))
		{
			ImGui::Text("UUID");
		}
	}

	void IDComponent::SetID(uint64 p_uuid)
	{
		m_UUID = UUID(p_uuid);
	}

	UUID IDComponent::GetID()
	{
		return m_UUID;
	}
}