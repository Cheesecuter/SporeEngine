#pragma once

#include <Types.hpp>
#include <Window.hpp>
#include <Files.hpp>
#include <SingletonInstance.hpp>

namespace Spore
{
	enum class AssetsType
	{
		TEXTURE,
		MODEL,
		SHADER,
		AUDIO
	};
	class FileExplorer : public Singleton<FileExplorer>
	{
	public:
		void Explorer(MainWindow* p_window, std::filesystem::path* p_path, AssetsType p_assets_type);

	protected:

	private:
		FileExplorer();
		~FileExplorer();
		friend class Singleton<FileExplorer>;
	};
}