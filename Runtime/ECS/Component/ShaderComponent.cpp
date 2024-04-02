#include <ShaderComponent.hpp>

namespace Spore
{
	ShaderComponent::ShaderComponent()
	{
		m_name = "Shader";
	}

	void ShaderComponent::AddShader(Shader* p_shader)
	{
		if (m_shaders.find(p_shader->m_identifier) != m_shaders.end())
		{
			m_shaders [p_shader->m_identifier]->m_shader = p_shader;
		}
		else
		{
			ShaderNode* shaderNode = new ShaderNode();
			shaderNode->m_shader = p_shader;
			m_shaders [p_shader->m_identifier] = shaderNode;
		}
	}

	void ShaderComponent::RemoveShader(Shader* p_shader)
	{
		m_shaders.erase(p_shader->m_identifier);
	}

	std::unordered_map<std::string, ShaderNode*> ShaderComponent::GetShaders() const
	{
		return m_shaders;
	}
}