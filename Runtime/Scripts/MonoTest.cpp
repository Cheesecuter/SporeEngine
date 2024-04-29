#include <MonoTest.h>

#include <iostream>
#include <string>
#include <fstream>

#include <mono/jit/jit.h>
#include <mono/metadata/attrdefs.h>
#include <mono/metadata/assembly.h>
#include <mono/metadata/mono-config.h>

MonoDomain* s_RootDomain = nullptr;
MonoDomain* s_AppDomain = nullptr;
MonoAssembly* s_AppAssembly = nullptr;

void InitMono()
{
	mono_set_assemblies_path("./SDKs/Mono/lib/4.5");

	MonoDomain* rootDomain = mono_jit_init("MyScriptRuntime");
	if (rootDomain == nullptr)
	{
		return;
	}

	s_RootDomain = rootDomain;

	s_AppDomain = mono_domain_create_appdomain(const_cast<char*>("MyAppDomain"), nullptr);
	mono_domain_set(s_AppDomain, true);
}

char* ReadBytes(const std::string& filepath, uint32_t* outSize)
{
	std::ifstream stream(filepath, std::ios::binary | std::ios::ate);

	if (!stream)
	{
		return nullptr;
	}

	std::streampos end = stream.tellg();
	stream.seekg(0, std::ios::beg);
	uint32_t size = end - stream.tellg();

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

MonoAssembly* LoadCSharpAssembly(const std::string& assemblyPath)
{
	uint32_t fileSize = 0;
	char* fileData = ReadBytes(assemblyPath, &fileSize);

	MonoImageOpenStatus status;
	MonoImage* image = mono_image_open_from_data_full(fileData, fileSize, 1, &status, 0);

	if (status != MONO_IMAGE_OK)
	{
		const char* errorMessage = mono_image_strerror(status);
		return nullptr;
	}

	MonoAssembly* assembly = mono_assembly_load_from_full(image, assemblyPath.c_str(), &status, 0);
	mono_image_close(image);

	delete [] fileData;
	
	return assembly;
}

void PrintAssemblyTypes(MonoAssembly* assembly)
{
	MonoImage* image = mono_assembly_get_image(assembly);
	const MonoTableInfo* typeDefinitionsTable = mono_image_get_table_info(image, MONO_TABLE_TYPEDEF);
	int32_t numTypes = mono_table_info_get_rows(typeDefinitionsTable);

	for (int32_t i = 0; i < numTypes; i++)
	{
		uint32_t cols [MONO_TYPEDEF_SIZE];
		mono_metadata_decode_row(typeDefinitionsTable, i, cols, MONO_TYPEDEF_SIZE);

		const char* nameSpace = mono_metadata_string_heap(image, cols [MONO_TYPEDEF_NAMESPACE]);
		const char* name = mono_metadata_string_heap(image, cols [MONO_TYPEDEF_NAME]);

		printf("%s.%s\n", nameSpace, name);
	}
}

MonoClass* GetClassInAssembly(MonoAssembly* assembly, const char* namespaceName, const char* className)
{
	MonoImage* image = mono_assembly_get_image(assembly);
	MonoClass* monoClass = mono_class_from_name(image, namespaceName, className);

	if (monoClass == nullptr)
	{
		return nullptr;
	}

	return monoClass;
}

MonoObject* InstantiateClass(const char* namespaceName, const char* className)
{
	MonoClass* testingClass = GetClassInAssembly(s_AppAssembly, "", "MonoTest");

	MonoObject* classInstance = mono_object_new(s_AppDomain, testingClass);

	if (classInstance == nullptr)
	{
		std::cout << "Class instance is nullptr" << std::endl;
		return nullptr;
	}

	mono_runtime_object_init(classInstance);

	return classInstance;
}

void CallPrintFloatVarMethod(MonoObject* objectInstance)
{
	MonoClass* instanceClass = mono_object_get_class(objectInstance);

	MonoMethod* method = mono_class_get_method_from_name(instanceClass, "PrintFloatVar", 0);

	if (method == nullptr)
	{
		return;
	}

	MonoObject* exception = nullptr;
	mono_runtime_invoke(method, objectInstance, nullptr, &exception);
}

void CallIncrementFloatVarMethod(MonoObject* objectInstance, float value)
{
	MonoClass* instanceClass = mono_object_get_class(objectInstance);

	MonoMethod* method = mono_class_get_method_from_name(instanceClass, "IncrementFloatVar", 1);

	if (method == nullptr)
	{
		return;
	}

	MonoObject* exception = nullptr;
	void* param = &value;
	mono_runtime_invoke(method, objectInstance, &param, &exception);

	// OR

	/*MonoObject* exception = nullptr;
	void* params [] = {
		&value
	};
	mono_runtime_invoke(method, objectInstance, params, &exception);*/
}

enum class Accessibility : uint8_t
{
	None = 0,
	Private = (1 << 0),
	Internal = (1 << 1),
	Protected = (1 << 2),
	Public = (1 << 3)
};

uint8_t GetFieldAccesibility(MonoClassField* field)
{
	uint8_t accesibility = (uint8_t) Accessibility::None;
	uint32_t accessFlag = mono_field_get_flags(field) & MONO_FIELD_ATTR_FIELD_ACCESS_MASK;

	switch (accessFlag)
	{
		case MONO_FIELD_ATTR_PRIVATE:
		{
			accesibility = (uint8_t) Accessibility::Private;
			break;
		}
		case MONO_FIELD_ATTR_FAM_AND_ASSEM:
		{
			accesibility |= (uint8_t) Accessibility::Protected;
			accesibility |= (uint8_t) Accessibility::Internal;
			break;
		}
		case MONO_FIELD_ATTR_ASSEMBLY:
		{
			accesibility |= (uint8_t) Accessibility::Internal;
			break;
		}
		case MONO_FIELD_ATTR_FAMILY:
		{
			accesibility |= (uint8_t) Accessibility::Protected;
			break;
		}
		case MONO_FIELD_ATTR_FAM_OR_ASSEM:
		{
			accesibility |= (uint8_t) Accessibility::Private;
			accesibility |= (uint8_t) Accessibility::Protected;
			break;
		}
		case MONO_FIELD_ATTR_PUBLIC:
		{
			accesibility |= (uint8_t) Accessibility::Public;
			break;
		}
	}

	return accesibility;
}

uint8_t GetPropertyAccessbility(MonoProperty* property)
{
	uint8_t accessibility = (uint8_t) Accessibility::None;

	MonoMethod* propertyGetter = mono_property_get_get_method(property);
	if (propertyGetter != nullptr)
	{
		uint32_t accessFlag = mono_method_get_flags(propertyGetter, nullptr) & MONO_METHOD_ATTR_ACCESS_MASK;

		switch (accessFlag)
		{
			case MONO_FIELD_ATTR_PRIVATE:
			{
				accessibility = (uint8_t) Accessibility::Private;
				break;
			}
			case MONO_FIELD_ATTR_FAM_AND_ASSEM:
			{
				accessibility = (uint8_t) Accessibility::Protected;
				accessibility = (uint8_t) Accessibility::Internal;
				break;
			}
			case MONO_FIELD_ATTR_ASSEMBLY:
			{
				accessibility = (uint8_t) Accessibility::Internal;
				break;
			}
			case MONO_FIELD_ATTR_FAMILY:
			{
				accessibility = (uint8_t) Accessibility::Protected;
				break;
			}
			case MONO_FIELD_ATTR_FAM_OR_ASSEM:
			{
				accessibility = (uint8_t) Accessibility::Private;
				accessibility = (uint8_t) Accessibility::Protected;
				break;
			}
			case MONO_FIELD_ATTR_PUBLIC:
			{
				accessibility = (uint8_t) Accessibility::Public;
				break;
			}
		}
	}

	MonoMethod* propertySetter = mono_property_get_set_method(property);
	if (propertySetter != nullptr)
	{
		uint32_t accessFlag = mono_method_get_flags(propertySetter, nullptr) & MONO_METHOD_ATTR_ACCESS_MASK;
		if (accessFlag != MONO_FIELD_ATTR_PUBLIC)
		{
			accessibility = (uint8_t) Accessibility::Private;
		}
	}
	else
	{
		accessibility = (uint8_t) Accessibility::Private;
	}

	return accessibility;
}

bool CheckMonoError(MonoError& error)
{
	bool hasError = !mono_error_ok(&error);
	if (hasError)
	{
		unsigned short errorCode = mono_error_get_error_code(&error);
		const char* errorMessage = mono_error_get_message(&error);
		printf("Mono Error\n");
		printf("\tError Code: %hu\n", errorCode);
		printf("\tError Message: %s\n", errorMessage);
		mono_error_cleanup(&error);
	}
	return hasError;
}

std::string MonoStringToUTF8(MonoString* monoString)
{
	if (monoString == nullptr || mono_string_length(monoString) == 0)
	{
		return "";
	}

	MonoError error;
	char* utf8 = mono_string_to_utf8_checked(monoString, &error);
	if (CheckMonoError(error))
	{
		return "";
	}
	std::string result(utf8);
	mono_free(utf8);
	return result;
}

static void Hello(MonoString* name)
{
	std::cout << "Hello, " << mono_string_to_utf8(name) << "!" << std::endl;
}

int main_MonoTest()
{
	InitMono();

	//s_AppAssembly = LoadCSharpAssembly("./Assets/Projects/MonoTest/MonoTest.dll");
	//s_AppAssembly = LoadCSharpAssembly("../../../ScriptEngine/ScriptEngine/bin/Debug/net6.0/ScriptEngine.dll");
	s_AppAssembly = LoadCSharpAssembly("D:/SporeEngine/ScriptEngine/ScriptEngine/bin/Debug/net6.0/ScriptEngine.dll");
	if (!s_AppAssembly)
	{
		std::cout << "assembly error" << std::endl;
	}
	//PrintAssemblyTypes(s_AppAssembly);

	mono_add_internal_call("Spore.HelloClass::Hello", reinterpret_cast<void*>(&Hello));

	void* args [1];
	args [0] = mono_array_new(s_AppDomain, mono_get_string_class(), 0);
	MonoClass* programClass = GetClassInAssembly(s_AppAssembly, "Spore", "MainClass");
	MonoMethod* mainMethod = mono_class_get_method_from_name(programClass, "Main", 1);
	MonoObject* result = mono_runtime_invoke(mainMethod, nullptr, args, nullptr);
	int resultCode = *static_cast<int*>(mono_object_unbox(result));

	return 0;
}