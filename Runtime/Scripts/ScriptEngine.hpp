#pragma once

#include <Object.hpp>
#include <Scene.hpp>
#include <ScriptHeaders.h>
#include <ScriptFieldInstance.hpp>
#include <ScriptClass.hpp>

namespace Spore
{
	class ScriptEngine
	{
	public:
		ScriptEngine();
		~ScriptEngine();

		static ScriptEngineData* s_data;

		static void Init();
		static void Terminate();
		static bool LoadAssembly(const std::filesystem::path& p_file_path);
		static bool LoadAppAssembly(const std::filesystem::path& p_file_path);
		static void ReloadAssembly();
		static void OnRuntimeStart(Scene* p_scene);
		static void OnRuntimeStop();
		static bool ObjectClassExists(const std::string& p_class_name);
		static void OnCreateObject(Object* p_object);
		static void OnUpdateObject(Object* p_object, float32 ts);
		static int InvokeMethods();
		static Scene* GetSceneContext();
		static sptr<ScriptInstance> GetObjectScriptInstance(UUID p_object_uuid);
		static sptr<ScriptClass> GetObjectClass(const std::string& p_name);
		static std::unordered_map<std::string, sptr<ScriptClass>> GetObjectClasses();
		static ScriptFieldMap& GetScriptFieldMap(Object p_object);
		static MonoImage* GetCoreAssemblyImage();
		static MonoObject* GetManagedInstance(UUID p_uuid);
		static MonoString* CreateString(const char* p_string);

	protected:

	private:
		static void InitMono();
		static void TerminateMono();
		static MonoObject* InstantiateClass(MonoClass* p_mono_class);
		static void LoadAssemblyClasses();

		friend class ScriptClass;
		friend class ScriptGlue;
	};
}