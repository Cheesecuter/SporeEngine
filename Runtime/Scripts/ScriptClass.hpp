#pragma once

#include <ScriptHeaders.h>
#include <UUID.hpp>

namespace Spore
{
	class ScriptEngine;

	class ScriptClass
	{
	public:
		ScriptClass() = default;
		ScriptClass(const std::string& p_class_namespace, 
					const std::string& p_class_name, 
					bool p_is_core = false);

		MonoObject* Instantiate();
		MonoMethod* GetMethod(const std::string& p_name, 
							  int p_parameter_count);
		MonoObject* InvokeMethod(MonoObject* p_instance, 
								 MonoMethod* p_method, 
								 void** p_params = nullptr);
		const std::map<std::string, ScriptField>& GetFields() const;

	protected:

	private:
		std::string m_class_namespace;
		std::string m_class_name;
		std::map<std::string, ScriptField> m_fields;
		MonoClass* m_mono_class = nullptr;

		friend class ScriptEngine;
	};
}