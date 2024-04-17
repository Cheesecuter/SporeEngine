#include <Audio.hpp>

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

	void WriteBuffer(unsigned char*& ptr, const std::string& str)
	{
		memcpy(ptr, str.c_str(), str.size());
		std::string spliter = "|";
		memcpy(ptr, spliter.c_str(), str.size() + spliter.size());
	}

	std::string ReadBuffer(const unsigned char*& ptr)
	{
		const unsigned char* start = ptr;
		while (*ptr != '|' && *ptr != '\0') ++ptr;
		std::string result(reinterpret_cast<const char*>(start), ptr - start);
		return result;
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
			std::cout << "ERROR::AUDIO::ERROR TYPE" << std::endl;
			return;
		}
		std::cout << "Audio imported: " << m_identifier << " from " << pathS << std::endl;
		AssetsManager::GetInstance().m_audio_mapper.insert(std::make_pair(m_identifier, this));
	}
}