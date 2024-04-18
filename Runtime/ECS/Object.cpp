#include <Object.hpp>

namespace Spore
{
	Object::Object(const std::string& p_identifier, const bool p_light) : m_identifier(p_identifier)
	{
		TransformComponent* transformComponent = new TransformComponent();
		AddComponent(transformComponent);
		transformComponent->SetReferencedObject(this);
		if (!p_light)
		{
			ShaderComponent* shaderComponent = new ShaderComponent();
			Shader* shader = AssetsManager::GetInstance().m_shader_mapper.find("ModelLoadingFragment.glsl")->second;
			m_model_shader = shader;
			shaderComponent->AddShader(m_model_shader);
			AddComponent(shaderComponent);
		}
	}

	Object::~Object()
	{
		m_components.clear();
		DeleteObject();
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
		
	}

	bool Object::AddComponent(Component* p_component)
	{
		bool returnFlag = true;
		try
		{
			m_components [p_component->GetName()] = p_component;
			p_component->SetReferencedObject(this);
		}
		catch (std::exception e)
		{
			returnFlag = false;
		}

		return returnFlag;
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

	Component* Object::GetComponent(const std::string& p_component_name)
	{
		for (std::pair<std::string, Component*> component : m_components)
		{
			if (component.second->GetName() == p_component_name)
			{
				return component.second;
			}
		}

		return nullptr;
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