#include <Texture.hpp>

namespace Spore
{
	Texture::Texture(const char* p_path)
	{
		LoadTexture(p_path);
	}

	Texture::~Texture()
	{
		AssetsManager::GetInstance().m_texture_mapper.erase(m_identifier);
	}

	uint32 Texture::LoadTexture(const char* p_path)
	{
		glGenTextures(1, &m_ID);

		int32 width, height, nrComponents;
		unsigned char* data = stbi_load(p_path, &width, &height, &nrComponents, 0);
		if (data)
		{
			uint32 format = GL_RED;
			if (nrComponents == 1)
				format = GL_RED;
			else if (nrComponents == 3)
				format = GL_RGB;
			else if (nrComponents == 4)
				format = GL_RGBA;

			glBindTexture(GL_TEXTURE_2D, m_ID);
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
			std::cout << "Texture failed to load at path: " << p_path << std::endl;
			stbi_image_free(data);
		}

		this->m_path = p_path;
		std::replace(this->m_path.begin(), this->m_path.end(), '\\', '/');
		m_identifier = this->m_path.substr(this->m_path.find_last_of('/') + 1, this->m_path.size());
		AssetsManager::GetInstance().m_texture_mapper.insert(std::make_pair(m_identifier, this));

		return m_ID;
	}
}