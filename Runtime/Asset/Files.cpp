#include <Files.hpp>

namespace Spore
{
	std::vector<fs::path> Files::m_root_paths;
	fs::path Files::m_project_path = std::filesystem::current_path();
	const fs::path Files::m_root_path = std::filesystem::current_path();

	Files::Files()
	{
	}

	Files::~Files()
	{
	}

	const fs::path Files::GetRootPath()
	{
		return m_root_path;
	}

	const fs::path Files::GetAssetsPath()
	{
		return GetRootPath() / "Assets";
	}

	const fs::path Files::GetShadersPath()
	{
		return GetRootPath() / "Assets/Shaders";
	}

	const fs::path Files::GetEditorPath()
	{
		return GetRootPath() / "Assets";
	}

	void Files::SetProjectPath(fs::path p_path)
	{
		m_project_path = p_path;
	}
	
	const fs::path Files::GetProjectPath()
	{
		return m_project_path;
	}
	
	std::vector<fs::path> Files::GetRootPaths()
	{
		if (m_root_paths.size() == 0)
		{
			for (uint32 i = 0; i < 26; i++)
			{
				char rootSymbol = 'A' + i;
				std::string tmpPath = "";
				tmpPath = tmpPath + rootSymbol + "://";

				fs::path p(tmpPath);
				if (fs::exists(p))
				{
					m_root_paths.push_back(p);
				}
			}
		}
		return m_root_paths;
	}
}