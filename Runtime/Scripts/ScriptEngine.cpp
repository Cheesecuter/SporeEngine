#include <ScriptEngine.hpp>
#include <ConsoleLogger.hpp>
#include <ScriptInstance.hpp>
#include <ScriptBinder.hpp>

namespace Spore
{
	static std::unordered_map<std::string, ScriptFieldType> s_script_field_typemap =
	{
		{ "System.Single", ScriptFieldType::Float },
		{ "System.Double", ScriptFieldType::Double },
		{ "System.Boolean", ScriptFieldType::Bool },
		{ "System.Char", ScriptFieldType::Char },
		{ "System.Int16", ScriptFieldType::Short },
		{ "System.Int32", ScriptFieldType::Int },
		{ "System.Int64", ScriptFieldType::Long },
		{ "System.Byte", ScriptFieldType::Byte },
		{ "System.UInt16", ScriptFieldType::UShort },
		{ "System.UInt32", ScriptFieldType::UInt },
		{ "System.UInt64", ScriptFieldType::ULong },

		{ "Spore.Vector2", ScriptFieldType::Vector2 },
		{ "Spore.Vector3", ScriptFieldType::Vector3 },
		{ "Spore.Vector4", ScriptFieldType::Vector4 },

		{ "Spore.Entity", ScriptFieldType::Entity },
	};

	static char* ReadBytes(const std::string& filepath, uint32_t* outSize);
	static MonoAssembly* LoadMonoAssembly(const std::filesystem::path& p_assembly_path,
										  bool p_load_PDB = false);
	ScriptFieldType MonoTypeToScriptFieldType(MonoType* p_mono_type);
	inline const char* ScriptFieldTypeToString(ScriptFieldType fieldType);
	inline ScriptFieldType ScriptFieldTypeFromString(std::string_view fieldType);

	ScriptEngineData* ScriptEngine::s_data = nullptr;

	ScriptEngine::ScriptEngine()
	{

	}

	ScriptEngine::~ScriptEngine()
	{

	}

	void ScriptEngine::Init()
	{
		s_data = new ScriptEngineData();

		InitMono();
		ScriptBinder::RegisterFunctions();

		bool status = LoadAssembly("D:/SporeEngine/ScriptEngine/ScriptEngine/bin/Debug/net4.5/Spore.dll");
		if (!status)
		{
			ConsoleLogger::GetInstance().Logger()->error("ScriptEngine::Init: Could not load ScriptCore assembly");
			return;
		}

		auto scriptModulePath = "D:/SporeEngine/ScriptEngine/ScriptEngine/bin/Debug/net4.5/Spore.dll";
		status = LoadAppAssembly(scriptModulePath);
		if (!status)
		{
			ConsoleLogger::GetInstance().Logger()->error("ScriptEngine::Init: Could not load app assembly");
			return;
		}

		LoadAssemblyClasses();

		ScriptBinder::RegisterComponents();
		s_data->m_object_class = new ScriptClass("Spore", "Object", true);
	}

	void ScriptEngine::Terminate()
	{
		TerminateMono();
		delete s_data;
	}

	void ScriptEngine::InitMono()
	{
		mono_set_assemblies_path("D:/SporeEngine/master/SporeEngine/SDKs/Mono/lib/mono/4.5");

		if (!s_data->m_enable_debugging)
		{

		}

		MonoDomain* rootDomain = mono_jit_init("SporeJITRuntime");
		//Assert(rootDomain);

		s_data->m_root_domain = rootDomain;

		if (s_data->m_enable_debugging)
		{

		}

		mono_thread_set_main(mono_thread_current());
	}

	void ScriptEngine::TerminateMono()
	{
		mono_domain_set(mono_get_root_domain(), false);

		mono_domain_unload(s_data->m_app_domain);
		s_data->m_app_domain = nullptr;

		mono_jit_cleanup(s_data->m_root_domain);
		s_data->m_root_domain = nullptr;
	}

	bool ScriptEngine::LoadAssembly(const std::filesystem::path& p_file_path)
	{
		s_data->m_app_domain = mono_domain_create_appdomain(const_cast<char*>("SporeScriptRuntime"), nullptr);
		mono_domain_set(s_data->m_app_domain, true);

		s_data->m_core_assembly_filepath = p_file_path;
		s_data->m_core_assembly = LoadMonoAssembly(p_file_path, s_data->m_enable_debugging);
		if (s_data->m_core_assembly == nullptr)
		{
			return false;
		}
		s_data->m_core_assembly_image = mono_assembly_get_image(s_data->m_core_assembly);
		return true;
	}

	bool ScriptEngine::LoadAppAssembly(const std::filesystem::path& p_file_path)
	{
		s_data->m_app_assembly_filepath = p_file_path;
		s_data->m_app_assembly = LoadMonoAssembly(p_file_path, s_data->m_enable_debugging);
		if (s_data->m_app_assembly == nullptr)
		{
			return false;
		}
		s_data->m_app_assembly_image = mono_assembly_get_image(s_data->m_app_assembly);
		s_data->m_assembly_reload_pending = false;
		return true;
	}

	void ScriptEngine::ReloadAssembly()
	{
		mono_domain_set(mono_get_root_domain(), false);

		mono_domain_unload(s_data->m_app_domain);

		LoadAssembly(s_data->m_core_assembly_filepath);
		LoadAppAssembly(s_data->m_app_assembly_filepath);
		LoadAssemblyClasses();

		ScriptBinder::RegisterComponents();

		s_data->m_object_class = new ScriptClass("Spore", "Object", true);
	}

	void ScriptEngine::OnRuntimeStart(Scene* p_scene)
	{
		s_data->m_scene_context = p_scene;
	}

	void ScriptEngine::OnRuntimeStop()
	{
		s_data->m_scene_context = nullptr;
		s_data->m_object_instances.clear();
	}

	bool ScriptEngine::ObjectClassExists(const std::string& p_class_name)
	{
		return s_data->m_object_classes.find(p_class_name) != s_data->m_object_classes.end();
	}

	void ScriptEngine::OnCreateObject(Object* p_object)
	{
		const auto& sc = p_object->GetComponent("Script");
		if (ScriptEngine::ObjectClassExists(sc->GetName()))
		{
			UUID objectID = p_object->GetUUID();

			sptr<ScriptInstance> instance = std::make_shared<ScriptInstance>(s_data->m_object_classes [sc->GetName()], p_object);
			s_data->m_object_instances [objectID] = instance;

			if (s_data->m_object_script_fields.find(objectID) != s_data->m_object_script_fields.end())
			{
				const ScriptFieldMap& fieldMap = s_data->m_object_script_fields.at(objectID);
				for (const auto& [name, fieldInstance] : fieldMap)
				{
					instance->SetFieldValueInternal(name, fieldInstance.m_buffer);
				}
			}

			instance->InvokeOnCreate();
		}
	}

	void ScriptEngine::OnUpdateObject(Object* p_object, float32 ts)
	{
		UUID objectID = p_object->GetUUID();
		if (s_data->m_object_instances.find(objectID) != s_data->m_object_instances.end())
		{
			sptr<ScriptInstance> instance = s_data->m_object_instances [objectID];
			instance->InvokeOnUpdate((float32) ts);
		}
		else
		{
			ConsoleLogger::GetInstance().Logger()->error("ScriptEngine::OnUpdateObject: Could not find ScriptInstance for object {}", uint64(objectID));
		}
	}

	int ScriptEngine::InvokeMethods()
	{
		MonoClass* main_class = mono_class_from_name(s_data->m_core_assembly_image, "Spore", "Program");

		const bool include_namespace = true;
		MonoMethodDesc* managed_method_desc = mono_method_desc_new("Spore.Program::Main()", include_namespace);
		MonoMethod* managed_method = mono_method_desc_search_in_class(managed_method_desc, main_class);
		mono_method_desc_free(managed_method_desc);

		MonoMethod* mainMethod = mono_class_get_method_from_name(main_class, "Main", 1);

		void* args [1];
		args [0] = mono_array_new(s_data->m_app_domain, mono_get_string_class(), 0);
		//mono_runtime_invoke(mainMethod, NULL, NULL, NULL);
		MonoObject* result = mono_runtime_invoke(mainMethod, nullptr, args, nullptr);
		int resultCode = *static_cast<int*>(mono_object_unbox(result));

		return resultCode;
	}

	Scene* ScriptEngine::GetSceneContext()
	{
		return s_data->m_scene_context;
	}

	sptr<ScriptInstance> ScriptEngine::GetObjectScriptInstance(UUID p_object_uuid)
	{
		auto it = s_data->m_object_instances.find(p_object_uuid);
		if (it == s_data->m_object_instances.end())
		{
			return nullptr;
		}
		return it->second;
	}

	sptr<ScriptClass> ScriptEngine::GetObjectClass(const std::string& p_name)
	{
		if (s_data->m_object_classes.find(p_name) == s_data->m_object_classes.end())
		{
			return nullptr;
		}
		return s_data->m_object_classes.at(p_name);
	}

	std::unordered_map<std::string, sptr<ScriptClass>> ScriptEngine::GetObjectClasses()
	{
		return s_data->m_object_classes;
	}

	ScriptFieldMap& ScriptEngine::GetScriptFieldMap(Object p_object)
	{
		UUID objectID = p_object.GetUUID();
		return s_data->m_object_script_fields [objectID];
	}

	void ScriptEngine::LoadAssemblyClasses()
	{
		s_data->m_object_classes.clear();

		const MonoTableInfo* typeDefinitionsTable = mono_image_get_table_info(s_data->m_app_assembly_image, MONO_TABLE_TYPEDEF);
		int32 numTypes = mono_table_info_get_rows(typeDefinitionsTable);
		MonoClass* objectClass = mono_class_from_name(s_data->m_core_assembly_image, "Spore", "Object");

		for (int32 i = 0; i < numTypes; i++)
		{
			uint32 cols [MONO_TYPEDEF_SIZE];
			mono_metadata_decode_row(typeDefinitionsTable, i, cols, MONO_TYPEDEF_SIZE);

			const char* nameSpace = mono_metadata_string_heap(s_data->m_app_assembly_image, cols [MONO_TYPEDEF_NAMESPACE]);
			const char* className = mono_metadata_string_heap(s_data->m_app_assembly_image, cols [MONO_TYPEDEF_NAME]);
			std::string fullName;
			if (strlen(nameSpace) != 0)
			{
				fullName = fmt::format("{}.{}", nameSpace, className);
			}
			else
			{
				fullName = className;
			}

			MonoClass* monoClass = mono_class_from_name(s_data->m_app_assembly_image, nameSpace, className);

			if (monoClass == objectClass)
			{
				continue;
			}

			bool isObject = mono_class_is_subclass_of(monoClass, objectClass, false);
			if (!isObject)
			{
				continue;
			}

			sptr<ScriptClass> scriptClass = std::make_shared<ScriptClass>(nameSpace, className);
			s_data->m_object_classes [fullName] = scriptClass;

			int32 fieldCount = mono_class_num_fields(monoClass);
			ConsoleLogger::GetInstance().Logger()->warn("ScriptEngine::OnUpdateObject: {} has {} fields:", className, fieldCount);
			void* iterator = nullptr;
			while (MonoClassField* field = mono_class_get_fields(monoClass, &iterator))
			{
				const char* fieldName = mono_field_get_name(field);
				uint32 flags = mono_field_get_flags(field);
				if (flags & FIELD_ATTRIBUTE_PUBLIC)
				{
					MonoType* type = mono_field_get_type(field);
					ScriptFieldType fieldType = MonoTypeToScriptFieldType(type);
					ConsoleLogger::GetInstance().Logger()->warn(" {} ({})", fieldName, ScriptFieldTypeToString(fieldType));
					scriptClass->m_fields [fieldName] = { fieldType, fieldName, field };
				}
			}
		}

		auto& objectClasses = s_data->m_object_classes;
	}

	MonoImage* ScriptEngine::GetCoreAssemblyImage()
	{
		return s_data->m_core_assembly_image;
	}

	MonoObject* ScriptEngine::GetManagedInstance(UUID p_uuid)
	{
		return s_data->m_object_instances.at(p_uuid)->GetManagerObject();
	}

	MonoString* ScriptEngine::CreateString(const char* p_string)
	{
		return mono_string_new(s_data->m_app_domain, p_string);
	}

	MonoObject* ScriptEngine::InstantiateClass(MonoClass* p_mono_class)
	{
		MonoObject* instance = mono_object_new(s_data->m_app_domain, p_mono_class);
		mono_runtime_object_init(instance);
		return instance;
	}

	static char* ReadBytes(const std::string& filepath, uint32_t* outSize)
	{
		std::ifstream stream(filepath, std::ios::binary | std::ios::ate);

		if (!stream)
		{
			return nullptr;
		}

		std::streampos end = stream.tellg();
		stream.seekg(0, std::ios::beg);
		uint32_t size = (uint32_t) (end - stream.tellg());

		if (size == 0)
		{
			return nullptr;
		}

		char* buffer = new char [size];
		stream.read((char*) buffer, size);
		stream.close();

		*outSize = size;
		return buffer;
	}

	static MonoAssembly* LoadMonoAssembly(const std::filesystem::path& p_assembly_path,
										  bool p_load_PDB)
	{
		uint32_t fileSize = 0;
		char* fileData = ReadBytes(p_assembly_path.string(), &fileSize);

		MonoImageOpenStatus status;
		MonoImage* image = mono_image_open_from_data_full(fileData, fileSize, 1, &status, 0);

		if (status != MONO_IMAGE_OK)
		{
			const char* errorMessage = mono_image_strerror(status);
			ConsoleLogger::GetInstance().Logger()->error("ScriptEngine::LoadMonoAssembly: {}", errorMessage);
			return nullptr;
		}

		if (p_load_PDB)
		{
			std::filesystem::path pdbPath = p_assembly_path;
			pdbPath.replace_extension(".pdb");

			if (std::filesystem::exists(pdbPath))
			{
				uint32_t pdbFileSize = 0;
				char* pdbFileData = ReadBytes(pdbPath.string(), &pdbFileSize);
				mono_debug_open_image_from_memory(image, (const mono_byte*)(pdbFileData), pdbFileSize);
				ConsoleLogger::GetInstance().Logger()->info("ScriptEngine::LoadAssembly: Loaded PDB {}", pdbPath.string().c_str());
			}
		}

		std::string pathString = p_assembly_path.string();
		MonoAssembly* assembly = mono_assembly_load_from_full(image, pathString.c_str(), &status, 0);
		mono_image_close(image);

		return assembly;
	}

	ScriptFieldType MonoTypeToScriptFieldType(MonoType* p_mono_type)
	{
		std::string typeName = mono_type_get_name(p_mono_type);

		auto it = s_script_field_typemap.find(typeName);
		if (it == s_script_field_typemap.end())
		{
			ConsoleLogger::GetInstance().Logger()->error("ScriptEngine::LoadAssemblyClasses: Unknown type: {}", typeName);
			return ScriptFieldType::None;
		}

		return it->second;
	}

	inline const char* ScriptFieldTypeToString(ScriptFieldType fieldType)
	{
		switch (fieldType)
		{
			case ScriptFieldType::None:    return "None";
			case ScriptFieldType::Float:   return "Float";
			case ScriptFieldType::Double:  return "Double";
			case ScriptFieldType::Bool:    return "Bool";
			case ScriptFieldType::Char:    return "Char";
			case ScriptFieldType::Byte:    return "Byte";
			case ScriptFieldType::Short:   return "Short";
			case ScriptFieldType::Int:     return "Int";
			case ScriptFieldType::Long:    return "Long";
			case ScriptFieldType::UByte:   return "UByte";
			case ScriptFieldType::UShort:  return "UShort";
			case ScriptFieldType::UInt:    return "UInt";
			case ScriptFieldType::ULong:   return "ULong";
			case ScriptFieldType::Vector2: return "Vector2";
			case ScriptFieldType::Vector3: return "Vector3";
			case ScriptFieldType::Vector4: return "Vector4";
			case ScriptFieldType::Entity:  return "Entity";
		}
		//ASSERT(false, "Unknown ScriptFieldType");
		return "None";
	}

	inline ScriptFieldType ScriptFieldTypeFromString(std::string_view fieldType)
	{
		if (fieldType == "None")    return ScriptFieldType::None;
		if (fieldType == "Float")   return ScriptFieldType::Float;
		if (fieldType == "Double")  return ScriptFieldType::Double;
		if (fieldType == "Bool")    return ScriptFieldType::Bool;
		if (fieldType == "Char")    return ScriptFieldType::Char;
		if (fieldType == "Byte")    return ScriptFieldType::Byte;
		if (fieldType == "Short")   return ScriptFieldType::Short;
		if (fieldType == "Int")     return ScriptFieldType::Int;
		if (fieldType == "Long")    return ScriptFieldType::Long;
		if (fieldType == "UByte")   return ScriptFieldType::UByte;
		if (fieldType == "UShort")  return ScriptFieldType::UShort;
		if (fieldType == "UInt")    return ScriptFieldType::UInt;
		if (fieldType == "ULong")   return ScriptFieldType::ULong;
		if (fieldType == "Vector2") return ScriptFieldType::Vector2;
		if (fieldType == "Vector3") return ScriptFieldType::Vector3;
		if (fieldType == "Vector4") return ScriptFieldType::Vector4;
		if (fieldType == "Entity")  return ScriptFieldType::Entity;

		//ASSERT(false, "Unknown ScriptFieldType");
		return ScriptFieldType::None;
	}
}