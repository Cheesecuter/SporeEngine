#pragma once

#include <Types.hpp>

namespace Spore
{
	template<class T>
	class Singleton
	{
	public:
		static T& GetInstance()
		{
			static T instance;
			return instance;
		}
		Singleton(T const&) = delete;
		void operator=(T const&) = delete;

	protected:
		Singleton()
		{

		}
	};
}
