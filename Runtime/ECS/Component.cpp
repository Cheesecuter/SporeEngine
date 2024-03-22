#include <Component.hpp>

namespace Spore
{
	Component::~Component() { }

	bool Component::IsDirty() const
	{
		return isDirty;
	}

	void Component::SetDirtyFlag(bool isDirty_p)
	{
		isDirty = isDirty_p;
	}

	std::string Component::GetName() const
	{
		return name;
	}
}