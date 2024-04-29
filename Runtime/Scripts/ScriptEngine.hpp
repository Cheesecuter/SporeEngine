#pragma once

#include <Types.hpp>

#include <mono/jit/jit.h>
#include <mono/metadata/attrdefs.h>
#include <mono/metadata/assembly.h>
#include <mono/metadata/mono-config.h>

namespace Spore
{
	class ScriptEngine
	{
	public:
		ScriptEngine();
		~ScriptEngine();
		void Init();
		MonoAssembly* GetAppAssembly();
		MonoAssembly* LoadAssembly(const std::string& p_assembly_path);
		MonoDomain* GetAppDomain();
		MonoClass* GetClassInAssembly(MonoAssembly* p_assembly, 
									  const char* p_namespace, 
									  const char* p_class_name);

	protected:

	private:
		bool m_initialized = false;
		MonoDomain* m_root_domain = nullptr;
		MonoDomain* m_app_domain = nullptr;
		MonoAssembly* m_app_assembly = nullptr;

	};
}