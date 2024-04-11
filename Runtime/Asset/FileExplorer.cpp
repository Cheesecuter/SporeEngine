#include <FileExplorer.hpp>

namespace Spore
{
	FileExplorer::FileExplorer()
	{

	}

	FileExplorer::~FileExplorer()
	{

	}

	void FileExplorer::Explorer(MainWindow* p_window, std::filesystem::path* p_path, AssetsType p_assets_type)
	{
		try
		{
			OPENFILENAME openFileName;
			TCHAR fileSize [512] = { 0 };

			ZeroMemory(&openFileName, sizeof(openFileName));
			openFileName.lStructSize = sizeof(openFileName);
			openFileName.lpstrFile = fileSize;
			openFileName.lpstrFile [0] = '\0';
			openFileName.nMaxFile = sizeof(fileSize);
			switch (p_assets_type)
			{
				case AssetsType::TEXTURE:
					openFileName.lpstrFilter = TEXT("Textures\0*.*\0");
					break;
				case AssetsType::MODEL:
					openFileName.lpstrFilter = TEXT("Models\0*.*\0");
					break;
				case AssetsType::SHADER:
					openFileName.lpstrFilter = TEXT("Shaders\0*.*\0");
					break;
				case AssetsType::AUDIO:
					openFileName.lpstrFilter = TEXT("Audios\0*.*\0");
					break;
				default:
					openFileName.lpstrFilter = TEXT("All\0*.*\0");
					break;
			}
			openFileName.nFilterIndex = 1;
			openFileName.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;

			if (GetOpenFileName(&openFileName) == TRUE)
			{
				std::filesystem::path filePath(openFileName.lpstrFile);
				*p_path = filePath;
			}
		}
		catch (const std::filesystem::filesystem_error& ex)
		{
			std::cerr << "Filesystem error: " << ex.what() << std::endl;
		}
	}
}