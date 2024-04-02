#pragma once
#ifndef FILES_HPP
#define FILES_HPP

#include <Types.hpp>
#include <SingletonInstance.hpp>

namespace fs = std::filesystem;
namespace Spore
{
	class Files : public Singleton<Files>
	{
	public:
		static const fs::path GetProjectPath();
		static const fs::path GetAssetsPath();
		static const fs::path GetShadersPath();
		static const fs::path GetEditorPath();
		static std::vector<fs::path> GetRootPaths();

	protected:

	private:
		static std::vector<fs::path> m_root_paths;
		static const fs::path m_run_path;

		Files();
		~Files();
		friend class Singleton<Files>;

	};
}

#endif
