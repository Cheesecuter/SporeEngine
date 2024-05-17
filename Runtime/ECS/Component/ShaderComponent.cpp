#include <ShaderComponent.hpp>
#include <Object.hpp>
#include <ModelObject.hpp>

namespace Spore
{
	ShaderComponent::ShaderComponent()
	{
		m_name = "Shader";
		m_button_image_delete = AssetsManager::GetInstance().m_texture_mapper ["delete.png"];
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
			std::vector<std::string> shadersToDelete;
			for (std::pair<std::string, ShaderNode*> it_shader : m_shaders)
			{
				ImGui::Selectable(it_shader.second->m_shader->m_identifier.c_str());
				std::string widgetID = "Inspector::Shader::Identifier::" + it_shader.second->m_shader->m_identifier;
				ImGui::PushID((widgetID + "::Popup").c_str());
				if (ImGui::BeginPopupContextItem())
				{
					ImGui::MenuItem("Rename", NULL, false, true);
					if (ImGui::MenuItem("Delete", NULL, false, true))
					{
						shadersToDelete.push_back(it_shader.second->m_shader->m_identifier);
					}
					if (ImGui::MenuItem("Set Uniforms", NULL, false, true))
					{
						m_show_adding_uniforms_panel = true;
						m_selected_shadernode = it_shader.second;
					}
					ImGui::Separator();
					if (ImGui::MenuItem("Close", NULL, false, true))
						ImGui::CloseCurrentPopup();
					ImGui::EndPopup();
				}
				ImGui::PopID();


				ImGui::PushID((widgetID + "::Is_Loading").c_str());
				ImGui::Checkbox("Is dLoading", &it_shader.second->m_is_loading);
				ImGui::PopID();

				ImGui::PushID((widgetID + "::Alpha_Filter").c_str());
				ImGui::Checkbox("Alpha Filter", &it_shader.second->m_shader->m_alpha_filter_flag);
				ImGui::PopID();

				ImGui::Separator();
			}
			for (int i = 0; i < shadersToDelete.size(); i++)
			{
				m_shaders.erase(shadersToDelete[i]);
			}
		}
		if (m_show_adding_uniforms_panel)
		{
			AddingUniformsPanel(m_selected_shadernode);
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
			std::vector<UniformNode*> uniforms;
			m_uniforms.insert(std::pair(shaderNode, uniforms));
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

	std::unordered_map<ShaderNode*, std::vector<UniformNode*>> ShaderComponent::GetUniforms() const
	{
		return m_uniforms;
	}

	void ShaderComponent::AddingUniformsPanel(ShaderNode* p_shadernode)
	{
		int32 width = 300;
		int32 height = 400;
		int32 textHeight = (int32) (ImGui::GetTextLineHeightWithSpacing() + ImGui::GetStyle().FramePadding.y * 0.5f);
		ImGuiIO& io = ImGui::GetIO();
		ImGui::SetNextWindowPos(ImVec2((float32) (io.DisplaySize.x / 2 - 100), (float32) (io.DisplaySize.y / 2 - 100)), ImGuiCond_Always);
		ImGui::SetNextWindowSize(ImVec2((float32) width, (float32) height), ImGuiCond_Always);
		ImGuiWindowFlags windowFlags = 0;
		windowFlags = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse;
		{
			ImGui::Begin(p_shadernode->m_shader->m_identifier.c_str(), &m_show_adding_uniforms_panel, windowFlags);

			const char* uniformTypes [] = {
				"Bool",
				"Int",
				"Float",
				"Vector 2",
				"Vector 3",
				"Vector 4",
				"Matrix 2",
				"Matrix 3",
				"Matrix 4"
			};
			static int currentUniformType = 0;
			static std::string selectedUniformType = "Bool";
			ImGui::Checkbox("Loading", &p_shadernode->m_is_loading);
			ImGui::Text("Uniform Type");
			ImGui::SameLine();
			if (ImGui::BeginCombo("##Uniform_Type", uniformTypes [currentUniformType]))
			{
				for (uint32 i = 0; i < IM_ARRAYSIZE(uniformTypes); i++)
				{
					const bool isSelected = (currentUniformType == i);
					if (ImGui::Selectable(uniformTypes [i], isSelected))
					{
						currentUniformType = i;
						selectedUniformType = std::string(uniformTypes [currentUniformType]);
					}
					if (isSelected)
					{
						ImGui::SetItemDefaultFocus();
					}
				}
				ImGui::EndCombo();
			}

			ImGui::Text("Uniform Name");
			ImGui::SameLine();
			static char uniformName [32] = "";
			ImGui::InputText("##Uniform_Name", uniformName, 32);
			std::string str = std::string(uniformName);

			m_uniform_name_exist = false;
			std::vector<UniformNode*>* uniforms = &m_uniforms.find(p_shadernode)->second;
			for (UniformNode* it_uniform : *uniforms)
			{
				if (it_uniform->m_name == str)
				{
					m_uniform_name_exist = true;
					break;
				}
			}

			if (ImGui::Button("Add Uniform"))
			{
				if (str == "" || m_uniform_name_exist)
				{
					m_uniform_name_illegal = true;
				}
				else
				{
					m_uniform_name_illegal = false;
					UniformNode* uniformNode = new UniformNode();
					uniformNode->m_name = str;
					if (selectedUniformType == "Bool")
					{
						uniformNode->m_type = ShaderUniformType::BOOL;
					}
					else if (selectedUniformType == "Int")
					{
						uniformNode->m_type = ShaderUniformType::INT;
					}
					else if (selectedUniformType == "Float")
					{
						uniformNode->m_type = ShaderUniformType::FLOAT;
					}
					else if (selectedUniformType == "Vector 2")
					{
						uniformNode->m_type = ShaderUniformType::VEC2;
					}
					else if (selectedUniformType == "Vector 3")
					{
						uniformNode->m_type = ShaderUniformType::VEC3;
					}
					else if (selectedUniformType == "Vector 4")
					{
						uniformNode->m_type = ShaderUniformType::VEC4;
					}
					else if (selectedUniformType == "Matrix 2")
					{
						uniformNode->m_type = ShaderUniformType::MAT2;
					}
					else if (selectedUniformType == "Matrix 3")
					{
						uniformNode->m_type = ShaderUniformType::MAT3;
					}
					else if (selectedUniformType == "Matrix 4")
					{
						uniformNode->m_type = ShaderUniformType::MAT4;
					}
					uniforms->push_back(uniformNode);
				}
			}
			if (m_uniform_name_illegal)
			{
				ImGui::Text("Illegal Uniform Name");
			}

			std::vector<std::string> uniformToDelete;

			for (UniformNode* it_uniform : *uniforms)
			{
				ImGui::PushID("Inspector::Shader::ImageButtonDeleteUniform");
				if (ImGui::ImageButton((ImTextureID) (intptr_t) m_button_image_delete->m_ID, ImVec2(13, 13)))
				{
				}
				if (ImGui::IsItemClicked())
				{
					uniformToDelete.push_back(it_uniform->m_name);
				}
				ImGui::PopID();
				ImGui::SameLine();
				ImGui::Text(it_uniform->m_name.c_str());
				ImGui::SameLine();
				std::string uniformID = "##" + it_uniform->m_name;
				if (it_uniform->m_type == ShaderUniformType::BOOL)
				{
					ImGui::Checkbox(uniformID.c_str(), &it_uniform->m_bool);
				}
				else if (it_uniform->m_type == ShaderUniformType::INT)
				{
					ImGui::DragInt(uniformID.c_str(), &it_uniform->m_int);
				}
				else if (it_uniform->m_type == ShaderUniformType::FLOAT)
				{
					ImGui::DragFloat(uniformID.c_str(), &it_uniform->m_float, 0.1f);
				}
				else if (it_uniform->m_type == ShaderUniformType::VEC2)
				{
					float32 uniformVec2 [2] = { it_uniform->m_vec2.x, it_uniform->m_vec2.y };
					ImGui::DragFloat2(uniformID.c_str(), uniformVec2, 0.1f);
					it_uniform->m_vec2.x = uniformVec2 [0];
					it_uniform->m_vec2.y = uniformVec2 [1];
				}
				else if (it_uniform->m_type == ShaderUniformType::VEC3)
				{
					float32 uniformVec3 [3] = { it_uniform->m_vec3.x, it_uniform->m_vec3.y, it_uniform->m_vec3.z };
					ImGui::DragFloat3(uniformID.c_str(), uniformVec3, 0.1f);
					it_uniform->m_vec3.x = uniformVec3 [0];
					it_uniform->m_vec3.y = uniformVec3 [1];
					it_uniform->m_vec3.z = uniformVec3 [2];
				}
				else if (it_uniform->m_type == ShaderUniformType::VEC4)
				{
					float32 uniformVec4 [4] = { it_uniform->m_vec4.x, it_uniform->m_vec4.y, it_uniform->m_vec4.z, it_uniform->m_vec4.w };
					ImGui::DragFloat4(uniformID.c_str(), uniformVec4, 0.1f);
					it_uniform->m_vec4.x = uniformVec4 [0];
					it_uniform->m_vec4.y = uniformVec4 [1];
					it_uniform->m_vec4.z = uniformVec4 [2];
					it_uniform->m_vec4.w = uniformVec4 [3];
				}
				else if (it_uniform->m_type == ShaderUniformType::MAT2)
				{
					float32 uniformMat20 [2] = { it_uniform->m_mat2 [0][0], it_uniform->m_mat2 [0][1] };
					float32 uniformMat21 [2] = { it_uniform->m_mat2 [1][0], it_uniform->m_mat2 [1][1] };
					ImGui::DragFloat2(uniformID.c_str(), uniformMat20, 0.1f);
					ImGui::DragFloat2(uniformID.c_str(), uniformMat21, 0.1f);
					it_uniform->m_mat2 [0][0] = uniformMat20 [0];
					it_uniform->m_mat2 [0][1] = uniformMat20 [1];
					it_uniform->m_mat2 [1][0] = uniformMat21 [0];
					it_uniform->m_mat2 [1][1] = uniformMat21 [1];
				}
				else if (it_uniform->m_type == ShaderUniformType::MAT3)
				{

				}
				else if (it_uniform->m_type == ShaderUniformType::MAT4)
				{

				}
			}

			for (std::string it_uniformName : uniformToDelete)
			{
				for (UniformNode* it_uniform : *uniforms)
				{
					if (it_uniform->m_name == it_uniformName)
					{
						uniforms->erase(std::remove(uniforms->begin(), uniforms->end(), it_uniform), uniforms->end());
					}
				}
			}
			uniformToDelete.clear();

			ImGui::End();
		}
	}
}