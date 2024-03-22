#include <AssetsManager.hpp>

namespace Spore
{
	class Shader;
	class Texture;
	class Model;

	std::map<std::string, Shader*> AssetsManager::shaderMapper;
	std::map<std::string, Texture*> AssetsManager::textureMapper;
	std::map<std::string, Model*> AssetsManager::modelMapper;
	std::unordered_map<std::string, int32> AssetsManager::modelCounter;

	AssetsManager::AssetsManager()
	{

	}

	AssetsManager::~AssetsManager()
	{

	}
}