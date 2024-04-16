#pragma once

namespace Spore
{
	class Object;

	class ObjectObserver
	{
	public:
		ObjectObserver();
		virtual ~ObjectObserver();
		virtual void OnObjectDeleted(Object* p_object);
	};
}