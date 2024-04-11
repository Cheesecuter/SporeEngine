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

		std::string GetIdentifier();
		std::string GetPath();

	protected:

	private:
		std::string m_identifier;
		std::string m_type;
		std::string m_path;
	};
}