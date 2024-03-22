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
		Texture(const char* path_p);
		~Texture();

		uint32 ID = NULL;
		std::string identifier;
		std::string type;
		std::string path;

		uint32 LoadTexture(const char* path_p);

	protected:

	private:

	};
}

#endif
