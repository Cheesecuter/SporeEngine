//#include <mono/jit/jit.h>
//#include <mono/metadata/assembly.h>
//
//#include <string>
//#include <iostream>
//#include <fstream>
//
//MonoDomain* s_RootDomain;
//MonoDomain* s_AppDomain;
//
//void InitMono()
//{
//    mono_set_assemblies_path("D:/SporeEngine/master/SporeEngine/SDKs/Mono/lib");
//
//    MonoDomain* rootDomain = mono_jit_init("MyScriptRuntime");
//    if (rootDomain == nullptr)
//    {
//        // Maybe log some error here
//        return;
//    }
//
//    // Store the root domain pointer
//    s_RootDomain = rootDomain;
//
//    char appDomainName [] = "MyAppDomain";
//    // Create an App Domain
//    s_AppDomain = mono_domain_create_appdomain(appDomainName, nullptr);
//    mono_domain_set(s_AppDomain, true);
//}
//
//char* ReadBytes(const std::string& filepath, uint32_t* outSize)
//{
//    std::ifstream stream(filepath, std::ios::binary | std::ios::ate);
//
//    if (!stream)
//    {
//        // ���ļ�ʧ��
//        return nullptr;
//    }
//
//    std::streampos end = stream.tellg();
//    stream.seekg(0, std::ios::beg);
//    uint32_t size = end - stream.tellg();
//
//    if (size == 0)
//    {
//        // �ļ�Ϊ��
//        return nullptr;
//    }
//
//    char* buffer = new char [size];
//    stream.read((char*) buffer, size);
//    stream.close();
//
//    *outSize = size;
//    return buffer;
//}
//
//MonoAssembly* LoadCSharpAssembly(const std::string& assemblyPath)
//{
//    uint32_t fileSize = 0;
//    char* fileData = ReadBytes(assemblyPath, &fileSize);
//
//    // ע�⣺���ǲ��ܶ����ͼ��ִ�г��˼��س���������κβ�������Ϊ���ͼ��û�жԳ��򼯵�����
//    MonoImageOpenStatus status;
//    MonoImage* image = mono_image_open_from_data_full(fileData, fileSize, 1, &status, 0);
//
//    if (status != MONO_IMAGE_OK)
//    {
//        const char* errorMessage = mono_image_strerror(status);
//        // ʹ�� errorMessage ���ݼ�¼һЩ������Ϣ
//        return nullptr;
//    }
//
//    MonoAssembly* assembly = mono_assembly_load_from_full(image, assemblyPath.c_str(), &status, 0);
//    mono_image_close(image);
//
//    // ��Ҫ�����ͷ��ļ�����
//    delete [] fileData;
//
//    return assembly;
//}
//
