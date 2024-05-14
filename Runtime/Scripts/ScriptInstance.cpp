#include <ScriptInstance.hpp>
#include <Object.hpp>
#include <ScriptClass.hpp>
#include <ScriptEngine.hpp>

namespace Spore
{
	ScriptInstance::ScriptInstance(sptr<ScriptClass> p_script_class, Object* p_object) :
		m_script_class(p_script_class)
	{
		m_instance = p_script_class->Instantiate();

		m_constructor = ScriptEngine::s_data->m_object_class->GetMethod(".ctor", 1);
		m_on_create_method = p_script_class->GetMethod("OnCreate", 0);
		m_on_update_method = p_script_class->GetMethod("OnUpdate", 1);

		{
			UUID objectID = p_object->GetUUID();
			void* param = &objectID;
			m_script_class->InvokeMethod(m_instance, m_constructor, &param);
		}
	}

	void ScriptInstance::InvokeOnCreate()
	{
		if (m_on_create_method)
		{
			m_script_class->InvokeMethod(m_instance, m_on_create_method);
		}
	}

	void ScriptInstance::InvokeOnUpdate(float32 p_ts)
	{
		if (m_on_update_method)
		{
			void* param = &p_ts;
			m_script_class->InvokeMethod(m_instance, m_on_update_method, &param);
		}
	}

	sptr<ScriptClass> ScriptInstance::GetScriptClass()
	{
		return m_script_class;
	}

	template<typename T>
	void ScriptInstance::SetFieldValue(const std::string& p_name, T p_value)
	{
		static_assert(sizeof(T) <= 16, "Type too large!");
		SetFieldValueInternal(p_name, p_value);
	}

	template<typename T>
	T ScriptInstance::GetFieldValue(const std::string& p_name)
	{
		static_assert(sizeof(T) <= 16, "Type too large!");
		bool success = GetFieldValueInternal(p_name, s_field_value_buffer);
		if (!success)
			return T();
		return *(T*) s_field_value_buffer;
	}

	MonoObject* ScriptInstance::GetManagerObject()
	{
		return m_instance;
	}

	bool ScriptInstance::SetFieldValueInternal(const std::string& p_name, 
											   const void* p_value)
	{
		const std::map<std::string, ScriptField>& fields = m_script_class->GetFields();
		std::map<std::string, ScriptField>::const_iterator it = fields.find(p_name);
		if (it == fields.end())
		{
			return false;
		}
		const ScriptField& field = it->second;
		mono_field_set_value(m_instance, field.m_class_field, (void*) p_value);
		return true;
	}

	bool ScriptInstance::GetFieldValueInternal(const std::string& p_name, 
											   void* p_buffer)
	{
		const std::map<std::string, ScriptField>& fields = m_script_class->GetFields();
		std::map<std::string, ScriptField>::const_iterator it = fields.find(p_name);
		if (it == fields.end())
		{
			return false;
		}
		const ScriptField& field = it->second;
		mono_field_get_value(m_instance, field.m_class_field, p_buffer);
		return true;
	}
}