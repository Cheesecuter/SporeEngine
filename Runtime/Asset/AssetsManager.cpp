#include <AssetsManager.hpp>

namespace Spore
{
	class Shader;
	class Texture;
	class Model;
	class Audio;

	std::map<std::string, Shader*> AssetsManager::m_shader_mapper;
	std::map<std::string, Texture*> AssetsManager::m_texture_mapper;
	std::map<std::string, Model*> AssetsManager::m_model_mapper;
	std::map<std::string, Audio*> AssetsManager::m_audio_mapper;
	std::unordered_map<std::string, int32> AssetsManager::m_model_counter;

	Shader* AssetsManager::m_selected_shader = nullptr;
	Texture* AssetsManager::m_selected_texture = nullptr;
	Model* AssetsManager::m_selected_model = nullptr;
	Audio* AssetsManager::m_selected_audio = nullptr;

	AssetsManager::AssetsManager()
	{

	}

	AssetsManager::~AssetsManager()
	{

	}
}