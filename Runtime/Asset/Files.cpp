#include <Files.hpp>

namespace Spore
{
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
}