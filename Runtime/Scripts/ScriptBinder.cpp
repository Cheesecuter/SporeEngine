#include <ScriptBinder.hpp>
#include <Types.hpp>
#include <ConsoleLogger.hpp>
#include <ScriptHeaders.h>
#include <ScriptEngine.hpp>
#include <UUID.hpp>
#include <Object.hpp>
#include <Scene.hpp>
#include <TransformComponent.hpp>

namespace Spore
{
	static std::unordered_map<MonoType*, std::function<bool(Object*)>> s_object_has_component_funcs;

	std::string MonoStringToString(MonoString* p_string);
#define SP_ADD_INTERNAL_CALL(Name) mono_add_internal_call("Spore.InternalCalls::", #Name, Name)

	static MonoObject* GetScriptInstance(UUID p_objectID)
	{
		return ScriptEngine::GetManagedInstance(p_objectID);
	}

	static bool Object_HasComponent(UUID p_objectID, MonoString* p_componentType)
	{
		std::string componentType = MonoStringToString(p_componentType);
		Scene* scene = ScriptEngine::GetSceneContext();
		if (scene == nullptr)
		{
			return false;
		}
		Object* object = scene->GetObjectByUUID(p_objectID);
		if (object == nullptr)
		{
			return false;
		}
		return object->HasComponent(componentType);
	}

	/*static bool Object_HasComponent(UUID p_objectID, MonoReflectionType* p_componentType)
	{
		Scene* scene = ScriptEngine::GetSceneContext();
		if (scene == nullptr)
		{
			return false;
		}
		Object* object = scene->GetObjectByUUID(p_objectID);
		if (object == nullptr)
		{
			return false;
		}
		MonoType* managedType = mono_reflection_type_get_type(p_componentType);
		if (managedType == nullptr)
		{
			return false;
		}
		bool res = s_object_has_component_funcs.at(managedType)(object);
		return res;
	}*/

	static uint64 Object_FindObjectByName(MonoString* p_name)
	{
		char* nameCStr = mono_string_to_utf8(p_name);
		Scene* scene = ScriptEngine::GetSceneContext();
		Object* object = scene->GetObjectByName(nameCStr);
		mono_free(nameCStr);

		if (!object)
		{
			return 0;
		}
		return object->GetUUID();
	}

	static void TransformComponent_SetPosition(UUID p_objectID, vec3f* p_translation)
	{
		Scene* scene = ScriptEngine::GetSceneContext();
		Object* object = scene->GetObjectByUUID(p_objectID);
		dynamic_cast<TransformComponent*>(object->GetComponent("Transform"))->SetPosition(*p_translation);
	}

	static void TransformComponent_GetPosition(UUID p_objectID, vec3f* p_out_translation)
	{
		Scene* scene = ScriptEngine::GetSceneContext();
		Object* object = scene->GetObjectByUUID(p_objectID);
		*p_out_translation = dynamic_cast<TransformComponent*>(object->GetComponent("Transform"))->GetPosition();
	}

	static void TransformComponent_SetRotation(UUID p_objectID, vec3f* p_translation)
	{
		Scene* scene = ScriptEngine::GetSceneContext();
		Object* object = scene->GetObjectByUUID(p_objectID);
		dynamic_cast<TransformComponent*>(object->GetComponent("Transform"))->SetRotation(*p_translation);
	}

	static void TransformComponent_GetRotation(UUID p_objectID, vec3f* p_out_translation)
	{
		Scene* scene = ScriptEngine::GetSceneContext();
		Object* object = scene->GetObjectByUUID(p_objectID);
		*p_out_translation = dynamic_cast<TransformComponent*>(object->GetComponent("Transform"))->GetRotation();
	}

	static void TransformComponent_SetScale(UUID p_objectID, vec3f* p_translation)
	{
		Scene* scene = ScriptEngine::GetSceneContext();
		Object* object = scene->GetObjectByUUID(p_objectID);
		dynamic_cast<TransformComponent*>(object->GetComponent("Transform"))->SetScale(*p_translation);
	}

	static void TransformComponent_GetScale(UUID p_objectID, vec3f* p_out_translation)
	{
		Scene* scene = ScriptEngine::GetSceneContext();
		Object* object = scene->GetObjectByUUID(p_objectID);
		*p_out_translation = dynamic_cast<TransformComponent*>(object->GetComponent("Transform"))->GetScale();
	}

	template<typename... Component>
	struct ComponentGroup
	{

	};

	using AllComponents = ComponentGroup<TransformComponent>;

	template<typename... Component>
	static void RegisterComponent()
	{
		([] ()
		{
			std::string_view typeName = typeid(Component).name();
			size_t pos = typeName.find_last_of(':');
			std::string_view structName = typeName.substr(pos + 1);
			std::string managedTypename = fmt::format("Spore.{}", structName);

			MonoType* managedType = mono_reflection_type_from_name(managedTypename.data(), ScriptEngine::GetCoreAssemblyImage());
			if (!managedType)
			{
				ConsoleLogger::GetInstance().Logger()->error("ScriptGlue::RegisterComponents: Could not find component type {}", managedTypename);
				return;
			}
			s_object_has_component_funcs [managedType] = [&managedTypename] (Object* object)
			{
				return object->HasComponent(managedTypename);
			};
		}(), ...);
	}

	template<typename... Component>
	static void RegisterComponent(ComponentGroup<Component...>)
	{
		RegisterComponent<Component...>();
	}

	void ScriptBinder::RegisterComponents()
	{
		s_object_has_component_funcs.clear();
		RegisterComponent(AllComponents{});
	}

	void ScriptBinder::RegisterFunctions()
	{
		mono_add_internal_call("Spore.InternalCalls::Object_HasComponent", reinterpret_cast<void*>(&Object_HasComponent));
		mono_add_internal_call("Spore.InternalCalls::Object_FindObjectByName", reinterpret_cast<void*>(&Object_FindObjectByName));
		mono_add_internal_call("Spore.InternalCalls::TransformComponent_SetPosition", reinterpret_cast<void*>(&TransformComponent_SetPosition));
		mono_add_internal_call("Spore.InternalCalls::TransformComponent_GetPosition", reinterpret_cast<void*>(&TransformComponent_GetPosition));
		mono_add_internal_call("Spore.InternalCalls::TransformComponent_SetRotation", reinterpret_cast<void*>(&TransformComponent_SetRotation));
		mono_add_internal_call("Spore.InternalCalls::TransformComponent_GetRotation", reinterpret_cast<void*>(&TransformComponent_GetRotation));
		mono_add_internal_call("Spore.InternalCalls::TransformComponent_SetScale", reinterpret_cast<void*>(&TransformComponent_SetScale));
		mono_add_internal_call("Spore.InternalCalls::TransformComponent_GetScale", reinterpret_cast<void*>(&TransformComponent_GetScale));
	}

	std::string MonoStringToString(MonoString* p_string)
	{
		char* cStr = mono_string_to_utf8(p_string);
		std::string str(cStr);
		mono_free(cStr);
		return str;
	}
}