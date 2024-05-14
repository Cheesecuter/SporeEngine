#include <ScriptClass.hpp>
#include <ScriptEngine.hpp>

namespace Spore
{
	ScriptClass::ScriptClass(const std::string& p_class_namespace, 
							 const std::string& p_class_name, 
							 bool p_is_core) : 
		m_class_namespace(p_class_namespace),
		m_class_name(p_class_name)
	{
		m_mono_class = mono_class_from_name(p_is_core ?
											ScriptEngine::s_data->m_core_assembly_image : ScriptEngine::s_data->m_app_assembly_image,
											p_class_namespace.c_str(),
											p_class_name.c_str());
	}

	MonoObject* ScriptClass::Instantiate()
	{
		return ScriptEngine::InstantiateClass(m_mono_class);
	}

	MonoMethod* ScriptClass::GetMethod(const std::string& p_name,
									   int p_parameter_count)
	{
		return mono_class_get_method_from_name(m_mono_class,
											   p_name.c_str(),
											   p_parameter_count);
	}

	MonoObject* ScriptClass::InvokeMethod(MonoObject* p_instance, 
										  MonoMethod* p_method, 
										  void** p_params)
	{
		MonoObject* exception = nullptr;
		return mono_runtime_invoke(p_method, p_instance,
								   p_params, &exception);
	}

	const std::map<std::string, ScriptField>& ScriptClass::GetFields() const
	{
		return m_fields;
	}
}