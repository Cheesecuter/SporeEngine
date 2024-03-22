#pragma once
#ifndef SHADER_COMPONENT_HPP
#define SHADER_COMPONENT_HPP

#include <Types.hpp>
#include <Component.hpp>
#include <Shader.hpp>

namespace Spore
{
	struct ShaderNode
	{
		bool isLoading = true;
		Shader* shader;
	};

	class ShaderComponent : public Component
	{
	public:
		ShaderComponent();
		void AddShader(Shader* shader_p);
		void RemoveShader(Shader* shader_p);
		std::unordered_map<std::string, ShaderNode*> GetShaders() const;

	protected:

	private:
		std::unordered_map<std::string, ShaderNode*> shaders;
	};
}

#endif
