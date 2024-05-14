#pragma once

#include <ScriptHeaders.h>

namespace Spore
{
	class ScriptFieldInstance
	{
	public:
		ScriptFieldInstance();
		~ScriptFieldInstance();

		ScriptField* m_field;

		template<typename T>
		void SetValue(T p_value);
		template<typename T>
		T GetValue();

	protected:

	private:
		uint8 m_buffer [16];

		friend class ScriptEngine;
		friend class ScriptInstance;
	};
}