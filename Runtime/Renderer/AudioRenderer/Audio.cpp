#include <Audio.hpp>

namespace Spore
{
	Audio::Audio(const char* p_path)
	{
		m_path = p_path;
		std::string pathS = p_path;
		std::replace(pathS.begin(), pathS.end(), '\\', '/');
		m_identifier = pathS.substr(pathS.find_last_of('/') + 1, pathS.size());
		AssetsManager::GetInstance().m_audio_mapper.insert(std::make_pair(m_identifier, this));
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