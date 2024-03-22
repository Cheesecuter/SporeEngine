#include <Files.hpp>

namespace Spore
{
	std::vector<fs::path> Files::rootPaths;
	const fs::path Files::runPath = std::filesystem::current_path();

	Files::Files()
	{
	}

	Files::~Files()
	{
	}

	const fs::path Files::GetProjectPath()
	{
		return runPath;
	}
	const fs::path Files::GetAssetsPath()
	{
		return GetProjectPath() / "Assets";
	}
	const fs::path Files::GetShadersPath()
	{
		return GetProjectPath() / "Assets/Shaders";
	}
	const fs::path Files::GetEditorPath()
	{
		return GetProjectPath() / "Assets";
	}
	std::vector<fs::path> Files::GetRootPaths()
	{
		if (rootPaths.size() == 0)
		{
			for (uint32 i = 0; i < 26; i++)
			{
				char rootSymbol = 'A' + i;
				std::string tmpPath = "";
				tmpPath = tmpPath + rootSymbol + "://";

				fs::path p(tmpPath);
				if (fs::exists(p))
				{
					rootPaths.push_back(p);
				}
			}
		}
		return rootPaths;
	}
}