#include <ShaderComponent.hpp>

namespace Spore
{
	ShaderComponent::ShaderComponent()
	{
		m_name = "Shader";
	}

	ShaderComponent::~ShaderComponent()
	{

	}

	void ShaderComponent::InspectorPanel()
	{
		if (ImGui::CollapsingHeader(m_name.c_str(), true))
		{
			for (std::pair<std::string, ShaderNode*> it_shader : m_shaders)
			{
				ImGui::Text(it_shader.second->m_shader->m_identifier.c_str());
				ImGui::Checkbox("Is dLoading", &it_shader.second->m_is_loading);
				ImGui::Checkbox("Alpha Filter", &it_shader.second->m_shader->m_alpha_filter_flag);
				ImGui::Separator();
			}
		}
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