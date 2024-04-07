#pragma once

#include <Types.hpp>

namespace Spore
{
	class Object;

	class Component
	{
	public:
		Component() = default;
		virtual ~Component();

		bool IsDirty() const;
		void SetDirtyFlag(bool p_is_dirty);
		std::string GetName() const;

	protected:
		std::string m_name = "";
		std::weak_ptr<Object> m_parents;
		bool m_is_dirty { false };
		bool m_is_scale_dirty { false };

	private:

	};
}
