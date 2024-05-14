#pragma once

#include <Types.hpp>

#include <mono/jit/jit.h>
#include <mono/metadata/attrdefs.h>
#include <mono/metadata/assembly.h>
#include <mono/metadata/object.h>
#include <mono/metadata/tabledefs.h>
#include <mono/metadata/mono-debug.h>
#include <mono/metadata/mono-config.h>
#include <mono/metadata/debug-helpers.h>
#include <mono/metadata/threads.h>

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

	class Scene;
	class ScriptClass;
	class ScriptFieldInstance;
	class ScriptInstance;
	class ScriptEngine;

	using ScriptFieldMap = std::unordered_map<std::string, ScriptFieldInstance>;

	struct ScriptEngineData
	{
		MonoDomain* m_root_domain = nullptr;
		MonoDomain* m_app_domain = nullptr;
		MonoAssembly* m_core_assembly = nullptr;
		MonoImage* m_core_assembly_image = nullptr;
		MonoAssembly* m_app_assembly = nullptr;
		MonoImage* m_app_assembly_image = nullptr;
		std::filesystem::path m_core_assembly_filepath;
		std::filesystem::path m_app_assembly_filepath;
		ScriptClass* m_object_class;
		std::unordered_map<std::string, sptr<ScriptClass>> m_object_classes;
		std::unordered_map<UUID, sptr<ScriptInstance>> m_object_instances;
		std::unordered_map<UUID, ScriptFieldMap> m_object_script_fields;
		//Scope<filewatch::FileWatch<std::string>> AppAssemblyFileWatcher;
		bool m_assembly_reload_pending = false;
		bool m_enable_debugging = true;
		Scene* m_scene_context = nullptr;
	};
}
