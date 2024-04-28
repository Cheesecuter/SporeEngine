#include <Audio.hpp>
#include <ConsoleLogger.hpp>

namespace Spore
{
	Audio::Audio(const char* p_path)
	{
		m_type = "Audio";
		LoadAsset(p_path);
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

	void Audio::LoadAsset(const char* p_path)
	{
		m_path = p_path;
		std::string pathS = p_path;
		std::replace(pathS.begin(), pathS.end(), '\\', '/');
		m_identifier = pathS.substr(pathS.find_last_of('/') + 1, pathS.size());
		std::string audioType = m_identifier.substr(m_identifier.find_last_of('.') + 1, m_identifier.size());
		if (audioType != "wav")
		{
			ConsoleLogger::GetInstance().Logger()->error("Audio::LoadAsset: Error type");
			return;
		}
		ConsoleLogger::GetInstance().Logger()->info("Audio::LoadAsset: Audio imported: {} from {}", m_identifier, pathS);
		AssetsManager::GetInstance().m_audio_mapper.insert(std::make_pair(m_identifier, this));
	}
}