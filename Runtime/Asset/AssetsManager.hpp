#pragma once

#include <Types.hpp>
#include <SingletonInstance.hpp>

namespace Spore
{
	class Shader;
	class Texture;
	class Model;

	class AssetsManager : public Singleton<AssetsManager>
	{
	public:
		static std::map<std::string, Shader*> m_shader_mapper;
		static std::map<std::string, Texture*> m_texture_mapper;
		static std::map<std::string, Model*> m_model_mapper;
		static std::unordered_map<std::string, int32> m_model_counter;

	protected:

	private:
		AssetsManager();
		~AssetsManager();
		friend class Singleton<AssetsManager>;
	};
}
