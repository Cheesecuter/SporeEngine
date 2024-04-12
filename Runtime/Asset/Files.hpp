#pragma once

#include <Types.hpp>
#include <SingletonInstance.hpp>

namespace fs = std::filesystem;
namespace Spore
{
	class Files : public Singleton<Files>
	{
	public:
		static const fs::path GetRootPath();
		static const fs::path GetAssetsPath();
		static const fs::path GetShadersPath();
		static const fs::path GetEditorPath();
		static void SetProjectPath(fs::path p_path);
		static const fs::path GetProjectPath();
		static std::vector<fs::path> GetRootPaths();

	protected:

	private:
		static std::vector<fs::path> m_root_paths;
		static std::vector<fs::path> m_project_paths;
		static const fs::path m_root_path;
		static fs::path m_project_path;

		Files();
		~Files();
		friend class Singleton<Files>;

	};
}
