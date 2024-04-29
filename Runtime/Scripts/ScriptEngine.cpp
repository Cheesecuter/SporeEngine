#include <ScriptEngine.hpp>
#include <ConsoleLogger.hpp>

namespace Spore
{
	char* ReadBytes(const std::string& p_file_path, uint32* p_out_size);

	ScriptEngine::ScriptEngine()
	{

	}

	ScriptEngine::~ScriptEngine()
	{

	}

	void ScriptEngine::Init()
	{
		if (!m_initialized)
		{
			m_initialized = true;

			mono_set_assemblies_path("./SDKs/Mono/lib/4.5");

			MonoDomain* rootDomain = mono_jit_init("ScriptRuntime");
			if (rootDomain == nullptr)
			{
				return;
			}

			m_root_domain = rootDomain;

			m_app_domain = mono_domain_create_appdomain(const_cast<char*>("AppDomain"), nullptr);
			mono_domain_set(m_app_domain, true);
		}
	}

	MonoAssembly* ScriptEngine::GetAppAssembly()
	{
		return m_app_assembly;
	}

	MonoAssembly* ScriptEngine::LoadAssembly(const std::string& p_assembly_path)
	{
		uint32 fileSize = 0;
		char* fileData = ReadBytes(p_assembly_path, &fileSize);

		MonoImageOpenStatus status;
		MonoImage* image = mono_image_open_from_data_full(fileData, fileSize, 1, &status, 0);

		if (status != MONO_IMAGE_OK)
		{
			const char* errorMessage = mono_image_strerror(status);
			return nullptr;
		}

		MonoAssembly* assembly = mono_assembly_load_from_full(image, p_assembly_path.c_str(), &status, 0);
		mono_image_close(image);

		delete [] fileData;

		return assembly;
	}

	MonoDomain* ScriptEngine::GetAppDomain()
	{
		return m_app_domain;
	}

	MonoClass* ScriptEngine::GetClassInAssembly(MonoAssembly* p_assembly, 
												const char* p_namespace, 
												const char* p_class_name)
	{
		MonoImage* image = mono_assembly_get_image(p_assembly);
		MonoClass* monoClass = mono_class_from_name(image, p_namespace, p_class_name);
	
		if (monoClass == nullptr)
		{
			ConsoleLogger::GetInstance().Logger()->error("Class {} not exist in namespace {}", p_class_name, p_namespace);
			return nullptr;
		}

		return monoClass;
	}

	char* ReadBytes(const std::string& p_file_path, uint32* p_out_size)
	{
		std::ifstream stream(p_file_path, std::ios::binary | std::ios::ate);

		if (!stream)
		{
			return nullptr;
		}

		std::streampos end = stream.tellg();
		stream.seekg(0, std::ios::beg);
		uint32 size = end - stream.tellg();

		if (size == 0)
		{
			return nullptr;
		}

		char* buffer = new char [size];
		stream.read((char*) buffer, size);
		stream.close();

		*p_out_size = size;
		return buffer;
	}
}