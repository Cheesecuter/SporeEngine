#pragma once
#ifndef ASSETS_MANAGER_HPP
#define ASSETS_MANAGER_HPP

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
		static std::map<std::string, Shader*> shaderMapper;
		static std::map<std::string, Texture*> textureMapper;
		static std::map<std::string, Model*> modelMapper;
		static std::unordered_map<std::string, int32> modelCounter;

	private:
		AssetsManager();
		~AssetsManager();
		friend class Singleton<AssetsManager>;
	};
}

#endif
