#include <Component.hpp>

namespace Spore
{
	Component::~Component()
	{

	}

	bool Component::IsDirty() const
	{
		return m_is_dirty;
	}

	void Component::SetDirtyFlag(bool p_is_dirty)
	{
		m_is_dirty = p_is_dirty;
	}

	std::string Component::GetName() const
	{
		return m_name;
	}

	void Component::SetReferencedObject(Object* p_object)
	{
		m_referenced_object = p_object;
	}

	Object* Component::GetReferencedObject()
	{
		return m_referenced_object;
	}

	void Component::InspectorPanel()
	{
		// Inspector UI implement

		/*if (ImGui::CollapsingHeader("Empty", true))
		{

		}*/
	}

	void Component::Tick(float32 p_delta_time)
	{
		// Tick implement
	}
}