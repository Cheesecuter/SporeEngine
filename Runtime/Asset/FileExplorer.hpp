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
		/**
		 * @brief Explore files in the file system.
		 *
		 * This function opens a file explorer dialog to select a file. It sets the selected file path to the provided path pointer.
		 *
		 * @param p_window Pointer to the main window.
		 * @param p_path Pointer to the path where the selected file path will be stored.
		 * @param p_assets_type Type of assets to filter in the file explorer.
		 */
		void Explorer(MainWindow* p_window, std::filesystem::path* p_path, AssetsType p_assets_type);

	protected:

	private:
		FileExplorer();
		~FileExplorer();
		friend class Singleton<FileExplorer>;
	};
}