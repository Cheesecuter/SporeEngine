#include <Audio.hpp>

namespace Spore
{
	Audio::Audio(std::filesystem::path p_path)
	{
		m_path = p_path.string();
	}

	Audio::~Audio()
	{
		AssetsManager::GetInstance().m_audio_mapper.erase(m_identifier);
	}

	std::string Audio::GetIdentifier()
	{
		return m_identifier;
	}

	std::string Audio::GetPath()
	{
		return m_path;
	}
}