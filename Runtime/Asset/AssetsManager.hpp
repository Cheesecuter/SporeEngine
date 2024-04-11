#pragma once

#include <Types.hpp>
#include <SingletonInstance.hpp>

namespace Spore
{
	class Shader;
	class Texture;
	class Model;
	class Audio;

	class AssetsManager : public Singleton<AssetsManager>
	{
	public:
		static std::map<std::string, Shader*> m_shader_mapper;
		static std::map<std::string, Texture*> m_texture_mapper;
		static std::map<std::string, Model*> m_model_mapper;
		static std::map<std::string, Audio*> m_audio_mapper;
		static std::unordered_map<std::string, int32> m_model_counter;

		static Shader* m_selected_shader;
		static Texture* m_selected_texture;
		static Model* m_selected_model;
		static Audio* m_selected_audio;

	protected:

	private:
		AssetsManager();
		~AssetsManager();
		friend class Singleton<AssetsManager>;
	};
}
