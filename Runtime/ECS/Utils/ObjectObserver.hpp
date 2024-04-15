#pragma once

#include <Types.hpp>

namespace Spore
{
	class Object;

	class ObjectObserver
	{
	public:
		virtual ~ObjectObserver();
		virtual void OnObjectDeleted(Object* p_object);
	};
}