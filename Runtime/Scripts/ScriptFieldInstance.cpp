#include <ScriptFieldInstance.hpp>

namespace Spore
{
	ScriptFieldInstance::ScriptFieldInstance()
	{

	}

	ScriptFieldInstance::~ScriptFieldInstance()
	{

	}

	template<typename T>
	void ScriptFieldInstance::SetValue(T p_value)
	{
		static_assert(sizeof(T) <= 16, "Type too large!");
		memcpy(m_buffer, &p_value, sizeof(T));
	}

	template<typename T>
	T ScriptFieldInstance::GetValue()
	{
		static_assert(sizeof(T) <= 16, "Type too large!");
		return *(T*) m_buffer;
	}
}