#pragma once

#include <Types.hpp>
#include <AssetsManager.hpp>

namespace Spore
{
	class Audio
	{
	public:
		Audio() = default;
		Audio(const char* p_path);
		virtual ~Audio();

		unsigned char* Serialize() const;
		static Audio* Deserialize(const unsigned char* p_buffer, size_t p_buffer_size);
		std::string GetIdentifier();
		std::string GetPath();
		
	protected:

	private:
		std::string m_identifier;
		std::string m_type;
		std::string m_path;

		void LoadAsset(const char* p_path);
	};
}