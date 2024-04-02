#include <Object.hpp>
#include <IMGUI_GLFW_OPENGL3.hpp>

namespace Spore
{
	Object::Object(const std::string& p_identifier, const bool p_light) : m_identifier(p_identifier)
	{
		TransformComponent* transformComponent = new TransformComponent();
		m_model_mapper = std::map<std::string, Model*>();
		m_components [transformComponent->GetName()] = transformComponent;
		if (!p_light)
		{
			ShaderComponent* shaderComponent = new ShaderComponent();
			Shader* shader = AssetsManager::GetInstance().m_shader_mapper.find("ModelLoadingFragment.glsl")->second;
			m_model_shader = shader;
			shaderComponent->AddShader(m_model_shader);
			//Shader* lightingShader = AssetsManager::GetInstance().shaderMapper.find("LightingFragment.glsl")->second;
			//shaderComponent->AddShader(lightingShader);
			m_components [shaderComponent->GetName()] = shaderComponent;
		}
	}

	Object::~Object()
	{
		for (std::map<std::string, Model*>::iterator it_model = m_model_mapper.begin(); it_model != m_model_mapper.end(); it_model++)
		{
			it_model->second->RemoveObserver(this);
		}
		m_components.clear();
		m_model_mapper.clear();
		DeleteObject();
	}

	void Object::AddModel(Model* p_model)
	{
		m_model_mapper.insert(std::make_pair(p_model->m_identifier, p_model));
		m_model_mapper [p_model->m_identifier]->AddObserver(this);
	}

	void Object::DeleteModel(Model* p_model)
	{
		m_model_mapper.erase(p_model->m_identifier);
		m_model_mapper [p_model->m_identifier]->RemoveObserver(this);
	}

	void Object::DeleteModel(std::string p_identifier)
	{
		m_model_mapper.erase(p_identifier);
		m_model_mapper [p_identifier]->RemoveObserver(this);
	}

	void Object::OnModelDeleted(Model* p_model)
	{
		m_model_mapper.erase(p_model->m_identifier);
		Object::~Object();
	}

	void Object::AddObserver(ObjectObserver* p_observer)
	{
		m_observer_list.push_back(p_observer);
	}

	void Object::RemoveObserver(ObjectObserver* p_observer)
	{
		const std::vector<ObjectObserver*>::iterator it = std::find(m_observer_list.begin(), m_observer_list.end(), p_observer);
		if (it != m_observer_list.end())
		{
			m_observer_list.erase(it);
		}
	}

	void Object::DeleteObject()
	{
		for (ObjectObserver* observer : m_observer_list)
		{
			observer->OnObjectDeleted(this);
		}
	}

	void Object::Update(float32 p_deltaTime)
	{

	}

	void Object::Render(std::vector<Shader*> p_shaders, Camera* p_camera,
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

	bool Object::HasComponent(const std::string& p_component_name) const
	{
		for (const std::pair<const std::string, Component*>& it_component : m_components)
		{
			if (it_component.second->GetName() == p_component_name)
			{
				return true;
			}
		}

		return false;
	}

	std::unordered_map<std::string, Component*> Object::GetComponents()
	{
		return m_components;
	}

	template<typename TComponent>
	TComponent* Object::TryGetComponent(const std::string& p_component_name)
	{
		for (Component& component : m_components)
		{
			if (component.GetName() == p_component_name)
			{
				return component;
			}
		}
	}

	/*template<typename TComponent>
	const TComponent* Object::TryGetComponentConst(const std::string& componentName) const
	{

	}*/

	void Object::SetPosition(const vec3f& p_position)
	{
		TransformComponent* transformComponent = dynamic_cast<TransformComponent*>(m_components.find("Transform")->second);
		transformComponent->SetPosition(p_position);
	}

	void Object::SetRotation(const vec3f& p_rotation)
	{
		TransformComponent* transformComponent = dynamic_cast<TransformComponent*>(m_components.find("Transform")->second);
		transformComponent->SetRotation(p_rotation);
	}

	void Object::SetScale(const vec3f& p_scale)
	{
		TransformComponent* transformComponent = dynamic_cast<TransformComponent*>(m_components.find("Transform")->second);
		transformComponent->SetScale(p_scale);
	}

	vec3f Object::GetPosition() const
	{
		TransformComponent* transformComponent = dynamic_cast<TransformComponent*>(m_components.find("Transform")->second);
		return transformComponent->GetPosition();
	}

	vec3f Object::GetRotation() const
	{
		TransformComponent* transformComponent = dynamic_cast<TransformComponent*>(m_components.find("Transform")->second);
		return transformComponent->GetRotation();
	}

	vec3f Object::GetScale() const
	{
		TransformComponent* transformComponent = dynamic_cast<TransformComponent*>(m_components.find("Transform")->second);
		return transformComponent->GetScale();
	}

	vec3f Object::GetFront() const
	{
		TransformComponent* transformComponent = dynamic_cast<TransformComponent*>(m_components.find("Transform")->second);
		return transformComponent->GetFront();
	}

	vec3f Object::GetRight() const
	{
		TransformComponent* transformComponent = dynamic_cast<TransformComponent*>(m_components.find("Transform")->second);
		return transformComponent->GetRight();
	}

	vec3f Object::GetUp() const
	{
		TransformComponent* transformComponent = dynamic_cast<TransformComponent*>(m_components.find("Transform")->second);
		return transformComponent->GetUp();
	}
}