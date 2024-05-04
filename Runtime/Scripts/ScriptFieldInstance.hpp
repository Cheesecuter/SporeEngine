#pragma once

#include <ScriptHeaders.h>

namespace Spore
{
	enum class ScriptFieldType
	{
		None = 0,
		Float, Double,
		Bool, Char, Byte, Short, Int, Long,
		UByte, UShort, UInt, ULong,
		Vector2, Vector3, Vector4,
		Entity
	};

	struct ScriptField
	{
		ScriptFieldType m_type;
		std::string m_name;

		MonoClassField* m_class_field;
	};

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