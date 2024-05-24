#pragma once

#include <ScriptHeaders.h>

namespace Spore
{
	class ScriptClass;
	class Object;

	class ScriptInstance
	{
	public:
		ScriptInstance(sptr<ScriptClass> p_script_class, Object* p_object);

		void InvokeOnCreate();
		void InvokeOnUpdate(float32 p_time_step);
		sptr<ScriptClass> GetScriptClass();
		template<typename T>
		void SetFieldValue(const std::string& p_name, T p_value);
		template<typename T>
		T GetFieldValue(const std::string& p_name);
		MonoObject* GetManagerObject();

	protected:

	private:
		sptr<ScriptClass> m_script_class;
		MonoObject* m_instance = nullptr;
		MonoMethod* m_constructor = nullptr;
		MonoMethod* m_on_create_method = nullptr;
		MonoMethod* m_on_update_method = nullptr;

		inline static char s_field_value_buffer [16];

		friend class ScriptEngine;
		friend class ScriptFieldInstance;

		bool SetFieldValueInternal(const std::string& p_name, const void* p_value);
		bool GetFieldValueInternal(const std::string& p_name, void* p_buffer);
	};
}