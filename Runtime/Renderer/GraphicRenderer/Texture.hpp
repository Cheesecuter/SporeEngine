#pragma once

#include <Types.hpp>
#include <AssetsManager.hpp>

namespace Spore
{
	class Texture
	{
	public:
		Texture() = default;
		Texture(const char* p_path);
		~Texture();

		uint32 m_ID = NULL;
		std::string m_identifier;
		std::string m_type;
		std::string m_path;

		uint32 LoadTexture(const char* p_path);

	protected:

	private:

	};
}
