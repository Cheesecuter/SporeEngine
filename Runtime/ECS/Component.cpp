#include <Component.hpp>

namespace Spore
{
	Component::~Component() { }

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
}