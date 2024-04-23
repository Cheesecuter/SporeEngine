#include <ShaderComponent.hpp>
#include <Object.hpp>
#include <ModelObject.hpp>

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
			ImGui::Text("Add Shader");
			if (ImGui::BeginDragDropTarget())
			{
				if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("AssetShaderDragDrop"))
				{
					const char* shaderIdentifier = static_cast<const char*>(payload->Data);
					Shader* shaderTemp = AssetsManager::GetInstance().m_shader_mapper [shaderIdentifier];
					if (shaderTemp != nullptr)
					{
						AddShader(shaderTemp);
					}
					ImGui::EndDragDropTarget();
				}
			}
			for (std::pair<std::string, ShaderNode*> it_shader : m_shaders)
			{
				ImGui::Text(it_shader.second->m_shader->m_identifier.c_str());
				std::string widgetID = "Inspector::Transform::Position::" + it_shader.second->m_shader->m_identifier;
				
				ImGui::PushID((widgetID + "::Is_Loading").c_str());
				ImGui::Checkbox("Is dLoading", &it_shader.second->m_is_loading);
				ImGui::PopID();
				ImGui::PushID((widgetID + "::Alpha_Filter").c_str());
				ImGui::Checkbox("Alpha Filter", &it_shader.second->m_shader->m_alpha_filter_flag);
				ImGui::PopID();
				ImGui::Separator();
			}
		}
	}

	void ShaderComponent::Tick(float32 p_delta_time)
	{
		ModelObject* object = dynamic_cast<ModelObject*>(GetReferencedObject());
		Model* model = object->GetModel();
		
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
			shaderNode->m_is_loading = true;
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