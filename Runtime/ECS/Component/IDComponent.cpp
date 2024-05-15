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
			std::string id = "UUID: " + std::to_string(uint64(m_UUID));
			ImGui::Text(id.c_str());
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