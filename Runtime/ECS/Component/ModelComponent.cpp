#include <ModelComponent.hpp>
#include <ShaderComponent.hpp>
#include <Object.hpp>

namespace Spore
{
	ModelComponent::ModelComponent()
	{
		m_name = "Model";
	}

	ModelComponent::~ModelComponent()
	{

	}

	void ModelComponent::InspectorPanel()
	{
		if (ImGui::CollapsingHeader(m_name.c_str(), true))
		{
			ImGui::Text("Model component");
			ImGui::Text("Add Model");
			if (ImGui::BeginDragDropTarget())
			{
				if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("AssetModelDragDrop"))
				{
					const char* modelIdentifier = static_cast<const char*>(payload->Data);
					Model* modelTemp = AssetsManager::GetInstance().m_model_mapper [modelIdentifier];
					if (modelTemp != nullptr)
					{
						m_model_mapper.clear();
						AddModel(modelTemp);
					}
					ImGui::EndDragDropTarget();
				}
			}
			ImGuiIO& io = ImGui::GetIO();
			for (std::pair<std::string, Model*> it_model : m_model_mapper)
			{
				ImGui::Separator();
				ImGui::Text(it_model.second->m_identifier.c_str());
				std::vector<Mesh*> meshes = it_model.second->GetMeshes();
				ImGui::Text("Meshes");
				for (Mesh* it_mesh : meshes)
				{
					ImGui::Separator();
					for (Texture*& it_texture : it_mesh->m_textures)
					{
						ImGui::Image((ImTextureID) (intptr_t) it_texture->m_ID, ImVec2(13, 13));
						if (ImGui::BeginDragDropTarget())
						{
							if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("AssetTextureDragDrop"))
							{
								const char* textureIdentifier = static_cast<const char*>(payload->Data);
								Texture* textureTemp = AssetsManager::GetInstance().m_texture_mapper [textureIdentifier];
								if (textureTemp != nullptr)
								{
									it_texture = textureTemp;
								}
								ImGui::EndDragDropTarget();
							}
						}
						float32 tex_w = (float32) 32;
						float32 tex_h = (float32) 32;
						ImVec4 tint_col = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
						ImVec4 border_col = ImGui::GetStyleColorVec4(ImGuiCol_Border);
						ImVec2 pos = ImGui::GetCursorScreenPos();
						if (ImGui::BeginItemTooltip())
						{
							float32 region_sz = 32.0f;
							float32 region_x = io.MousePos.x - pos.x - region_sz * 0.5f;
							float32 region_y = io.MousePos.y - pos.y - region_sz * 0.5f;
							float32 zoom = 4.0f;
							if (region_x < 0.0f)
							{
								region_x = 0.0f;
							}
							else if (region_x > tex_w - region_sz)
							{
								region_x = tex_w - region_sz;
							}
							if (region_y < 0.0f)
							{
								region_y = 0.0f;
							}
							else if (region_y > tex_h - region_sz)
							{
								region_y = tex_h - region_sz;
							}
							ImVec2 uv0 = ImVec2((region_x) / tex_w, (region_y) / tex_h);
							ImVec2 uv1 = ImVec2((region_x + region_sz) / tex_w, (region_y + region_sz) / tex_h);
							ImGui::Image((ImTextureID) (intptr_t) it_texture->m_ID, ImVec2(region_sz * zoom, region_sz * zoom), uv0, uv1, tint_col, border_col);
							ImGui::EndTooltip();
						}
						ImGui::SameLine();
						ImGui::Text(it_texture->m_identifier.c_str());
						ImGui::Text("Add Texture");
						
						ImGui::SetItemTooltip(it_texture->m_identifier.c_str());
					}
				}
			}
		}
	}

	void ModelComponent::Tick(float32 p_delta_time)
	{
		ShaderComponent* shaderComponent = dynamic_cast<ShaderComponent*>(GetReferencedObject()->GetComponent("Shader"));
		Model* model = m_model_mapper.begin()->second;
		std::unordered_map<ShaderNode*, std::vector<UniformNode*>> uniforms = shaderComponent->GetUniforms();

		for (std::pair<ShaderNode*, std::vector<UniformNode*>> it_shader : uniforms)
		{
			if (it_shader.first->m_is_loading)
			{
				it_shader.first->m_shader->Use();
				it_shader.first->m_shader->SetMat4("projection", m_model_transform_matrix_node.m_projection);
				it_shader.first->m_shader->SetMat4("view", m_model_transform_matrix_node.m_view);
				it_shader.first->m_shader->SetMat4("model", m_model_transform_matrix_node.m_model);
				for (UniformNode* it_uniform : it_shader.second)
				{
					if (it_uniform->m_type == ShaderUniformType::BOOL)
					{
						it_shader.first->m_shader->SetBool(it_uniform->m_name, it_uniform->m_bool);
					}
					else if (it_uniform->m_type == ShaderUniformType::INT)
					{
						it_shader.first->m_shader->SetInt(it_uniform->m_name, it_uniform->m_int);
					}
					else if (it_uniform->m_type == ShaderUniformType::FLOAT)
					{
						it_shader.first->m_shader->SetFloat(it_uniform->m_name, it_uniform->m_float);
					}
					else if (it_uniform->m_type == ShaderUniformType::VEC2)
					{
						it_shader.first->m_shader->SetVec2(it_uniform->m_name, it_uniform->m_vec2);
					}
					else if (it_uniform->m_type == ShaderUniformType::VEC3)
					{
						it_shader.first->m_shader->SetVec3(it_uniform->m_name, it_uniform->m_vec3);
					}
					else if (it_uniform->m_type == ShaderUniformType::VEC4)
					{
						it_shader.first->m_shader->SetVec4(it_uniform->m_name, it_uniform->m_vec4);
					}
				}
				model->Draw(*(it_shader.first->m_shader));
			}
		}
	}

	void ModelComponent::OnModelDeleted(Model* p_model)
	{
		m_model_mapper.erase(p_model->m_identifier);
	}

	void ModelComponent::SetModelType(ModelType p_model_type)
	{
		m_model_type = p_model_type;
	}
	
	ModelType ModelComponent::GetModelType()
	{
		return m_model_type;
	}

	void ModelComponent::SetModelTransformMatrixNode(ModelTransformMatrixNode p_model_transform_matrix_node)
	{
		m_model_transform_matrix_node = p_model_transform_matrix_node;
	}
	
	void ModelComponent::SetModelTransformMatrixNode(mat4f p_projection, mat4f p_view, mat4f p_model)
	{
		m_model_transform_matrix_node.m_projection = p_projection;
		m_model_transform_matrix_node.m_view = p_view;
		m_model_transform_matrix_node.m_model = p_model;
	}

	ModelTransformMatrixNode ModelComponent::GetModelTransformMatrixNode()
	{
		return m_model_transform_matrix_node;
	}

	void ModelComponent::AddModel(Model* p_model)
	{
		m_model_mapper.insert(std::make_pair(p_model->m_identifier, p_model));
		m_model_mapper [p_model->m_identifier]->AddObserver(this);
	}

	Model* ModelComponent::GetModel()
	{
		if (m_model_mapper.empty())
		{
			return nullptr;
		}
		return m_model_mapper.begin()->second;
	}

	void ModelComponent::DeleteModel(std::string p_identifier)
	{
		m_model_mapper.erase(p_identifier);
		m_model_mapper [p_identifier]->RemoveObserver(this);
	}
}