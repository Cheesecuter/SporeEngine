#include <Texture.hpp>
#include <AssetsManager.hpp>

namespace Spore
{
	Texture::Texture(const char* path)
	{
		LoadTexture(path);
	}

	Texture::~Texture()
	{
		AssetsManager::GetInstance().textureMapper.erase(identifier);
	}

	// utility function for loading a 2D texture from file
	uint32 Texture::LoadTexture(const char* path)
	{
		glGenTextures(1, &ID);

		int32 width, height, nrComponents;
		unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);
		if (data)
		{
			uint32 format = GL_RED;
			if (nrComponents == 1)
				format = GL_RED;
			else if (nrComponents == 3)
				format = GL_RGB;
			else if (nrComponents == 4)
				format = GL_RGBA;

			glBindTexture(GL_TEXTURE_2D, ID);
			glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			stbi_image_free(data);
		}
		else
		{
			std::cout << "Texture failed to load at path: " << path << std::endl;
			stbi_image_free(data);
		}

		this->path = path;
		std::replace(this->path.begin(), this->path.end(), '\\', '/');
		identifier = this->path.substr(this->path.find_last_of('/') + 1, this->path.size());
		AssetsManager::GetInstance().textureMapper.insert(std::make_pair(identifier, this));

		return ID;
	}
}