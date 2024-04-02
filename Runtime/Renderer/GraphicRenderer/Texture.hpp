#pragma once
#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <Types.hpp>

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

#endif
