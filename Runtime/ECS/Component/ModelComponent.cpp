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
			for (std::pair<std::string, Model*> it_model : m_model_mapper)
			{
				ImGui::Separator();
				ImGui::Text(it_model.second->m_identifier.c_str());
			}
		}
	}

	void ModelComponent::Tick(float32 p_delta_time)
	{
		ShaderComponent* shaderComponent = dynamic_cast<ShaderComponent*>(GetReferencedObject()->GetComponent("Shader"));
		Model* model = m_model_mapper.begin()->second;
		for (std::pair<std::string, ShaderNode*> it_shader : shaderComponent->GetShaders())
		{
			if (it_shader.second->m_is_loading)
			{
				it_shader.second->m_shader->Use();
				it_shader.second->m_shader->SetBool("alphaFilterFlag", it_shader.second->m_shader->m_alpha_filter_flag);
				it_shader.second->m_shader->SetMat4("projection", m_model_transform_matrix_node.m_projection);
				it_shader.second->m_shader->SetMat4("view", m_model_transform_matrix_node.m_view);
				it_shader.second->m_shader->SetMat4("model", m_model_transform_matrix_node.m_model);
				model->Draw(*(it_shader.second->m_shader));
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