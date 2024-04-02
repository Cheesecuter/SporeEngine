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
		bool m_is_loading = true;
		Shader* m_shader;
	};

	class ShaderComponent : public Component
	{
	public:
		ShaderComponent();
		void AddShader(Shader* p_shader);
		void RemoveShader(Shader* p_shader);
		std::unordered_map<std::string, ShaderNode*> GetShaders() const;

	protected:

	private:
		std::unordered_map<std::string, ShaderNode*> m_shaders;
	};
}

#endif
