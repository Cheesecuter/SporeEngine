#include <ModelObject.hpp>

namespace Spore
{
	ModelObject::ModelObject(const std::string& p_identifier) : Object(p_identifier)
	{
		m_type = "model";
		m_model_mapper = std::map<std::string, Model*>();
		ShaderComponent* shaderComponent = new ShaderComponent();
		Shader* shader = AssetsManager::GetInstance().m_shader_mapper.find("ModelLoadingFragment.glsl")->second;
		m_model_shader = shader;
		shaderComponent->AddShader(m_model_shader);
		m_components [shaderComponent->GetName()] = shaderComponent;
	}

	ModelObject::~ModelObject()
	{
		for (std::map<std::string, Model*>::iterator it_model = m_model_mapper.begin(); it_model != m_model_mapper.end(); it_model++)
		{
			it_model->second->RemoveObserver(this);
		}
		m_components.clear();
		m_model_mapper.clear();
		DeleteObject();
	}

	void ModelObject::AddModel(Model* p_model)
	{
		m_model_mapper.insert(std::make_pair(p_model->m_identifier, p_model));
		m_model_mapper [p_model->m_identifier]->AddObserver(this);
	}

	void ModelObject::DeleteModel(Model* p_model)
	{
		m_model_mapper.erase(p_model->m_identifier);
		m_model_mapper [p_model->m_identifier]->RemoveObserver(this);
	}

	void ModelObject::DeleteModel(std::string p_identifier)
	{
		m_model_mapper.erase(p_identifier);
		m_model_mapper [p_identifier]->RemoveObserver(this);
	}

	void ModelObject::OnModelDeleted(Model* p_model)
	{
		m_model_mapper.erase(p_model->m_identifier);
		ModelObject::~ModelObject();
	}

	void ModelObject::Render(std::vector<Shader*> p_shaders, Camera* p_camera,
						uint32 p_screen_width, uint32 p_screen_height,
						mat4f p_projection, mat4f p_view, mat4f p_model)
	{
		p_projection = glm::perspective(glm::radians(p_camera->m_zoom),
										(float32) p_screen_width / (float32) p_screen_height, 0.1f, 10000.0f);
		p_view = p_camera->GetViewMatrix();

		TransformComponent* transformComponent = dynamic_cast<TransformComponent*>(m_components.find("Transform")->second);
		ShaderComponent* shaderComponent = nullptr;
		Model* model = nullptr;
		p_model = transformComponent->GetMatrix();
		for (std::map<std::string, Model*>::iterator it_model = m_model_mapper.begin(); it_model != m_model_mapper.end(); it_model++)
		{
			model = it_model->second;
			shaderComponent = dynamic_cast<ShaderComponent*>(m_components.find("Shader")->second);
			for (uint32 i = 0; i < p_shaders.size(); i++)
			{
				shaderComponent->AddShader(p_shaders [i]);
			}

			for (std::pair<std::string, ShaderNode*> it_shader : shaderComponent->GetShaders())
			{
				if (it_shader.second->m_is_loading)
				{
					it_shader.second->m_shader->Use();
					it_shader.second->m_shader->SetBool("alphaFilterFlag", it_shader.second->m_shader->m_alpha_filter_flag);
					it_shader.second->m_shader->SetMat4("projection", p_projection);
					it_shader.second->m_shader->SetMat4("view", p_view);
					it_shader.second->m_shader->SetMat4("model", p_model);
					model->Draw(*(it_shader.second->m_shader));
				}
			}
		}
	}
}