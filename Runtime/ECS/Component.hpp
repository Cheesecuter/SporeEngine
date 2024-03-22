#pragma once
#ifndef COMPONENT_HPP
#define COMPONENT_HPP

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
		void SetDirtyFlag(bool isDirty_p);
		std::string GetName() const;

	protected:
		std::string name = "";
		std::weak_ptr<Object> parents;
		bool isDirty { false };
		bool isScaleDirty { false };

	private:

	};
}

#endif
