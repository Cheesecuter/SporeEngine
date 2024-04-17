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

	unsigned char* Audio::Serialize() const
	{
		size_t totalSize = m_identifier.size() + m_type.size() + m_path.size();
		unsigned char* buffer = new unsigned char [totalSize];
		unsigned char* ptr = buffer;
		std::string str = m_identifier + "|" + m_type + "|" + m_path;
		memcpy(ptr, str.c_str(), str.size());
		return buffer;
	}

	Audio* Audio::Deserialize(const unsigned char* p_buffer, size_t p_buffer_size)
	{
		Audio* audio = nullptr;
		const unsigned char* ptr = p_buffer;
		audio->m_identifier = ReadBuffer(ptr);
		++ptr;
		audio->m_type = ReadBuffer(ptr);
		++ptr;
		audio->m_path = ReadBuffer(ptr);
		return audio;
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