#include <Object.hpp>
#include <IMGUI_GLFW_OPENGL3.hpp>

namespace Spore
{
	Object::Object(const std::string& identifier_p, const bool light_p) : identifier(identifier_p)
	{
		TransformComponent* transformComponent = new TransformComponent();
		modelMapper = std::map<std::string, Model*>();
		components [transformComponent->GetName()] = transformComponent;
		if (!light_p)
		{
			ShaderComponent* shaderComponent = new ShaderComponent();
			Shader* shader = AssetsManager::GetInstance().shaderMapper.find("ModelLoadingFragment.glsl")->second;
			modelShader = shader;
			shaderComponent->AddShader(modelShader);
			//Shader* lightingShader = AssetsManager::GetInstance().shaderMapper.find("LightingFragment.glsl")->second;
			//shaderComponent->AddShader(lightingShader);
			components [shaderComponent->GetName()] = shaderComponent;
		}
	}

	Object::~Object()
	{
		for (const std::pair<std::string, Model*> it_model : modelMapper)
		{
			delete it_model.second;
		}
		for (const std::pair<const std::string, Component*>& it_component : components)
		{
			delete it_component.second;
		}
		components.clear();
		modelMapper.clear();
		DeleteObject();
	}

	void Object::AddModel(Model* model_p)
	{
		modelMapper.insert(std::make_pair(model_p->identifier, model_p));
	}

	void Object::DeleteModel(Model model_p)
	{
		std::map<std::string, Model*>::iterator it = modelMapper.find(model_p.identifier);
		if (it != modelMapper.end())
		{
			modelMapper.erase(it->first);
		}
	}

	void Object::DeleteModel(std::string identifier_p)
	{
		modelMapper.erase(identifier_p);
	}

	void Object::OnModelDeleted(Model* model)
	{
		modelMapper.erase(model->identifier);
		Object::~Object();
	}

	void Object::AddObserver(std::shared_ptr<ObjectObserver> observer_p)
	{
		observerList.push_back(observer_p);
	}

	void Object::RemoveObserver(std::shared_ptr<ObjectObserver> observer_p)
	{
		const std::vector<std::shared_ptr<ObjectObserver>>::iterator it = std::find(observerList.begin(), observerList.end(), observer_p);
		if (it != observerList.end())
		{
			observerList.erase(it);
		}
	}

	void Object::DeleteObject()
	{
		for (std::shared_ptr<ObjectObserver> observer : observerList)
		{
			observer->OnObjectDeleted(this);
		}
	}

	void Object::Update(float32 deltaTime)
	{

	}

	void Object::Render(std::vector<Shader*> shaders_p, Camera* camera_p,
						uint32 scrWidth_p, uint32 scrHeight_p,
						mat4f projection_p, mat4f view_p, mat4f model_p)
	{
		projection_p = glm::perspective(glm::radians(camera_p->Zoom),
										(float32) scrWidth_p / (float32) scrHeight_p, 0.1f, 10000.0f);
		view_p = camera_p->GetViewMatrix();

		TransformComponent* transformComponent = dynamic_cast<TransformComponent*>(components.find("Transform")->second);
		ShaderComponent* shaderComponent = nullptr;
		Model* model = nullptr;
		model_p = transformComponent->GetMatrix();
		for (std::map<std::string, Model*>::iterator it_model = modelMapper.begin(); it_model != modelMapper.end(); it_model++)
		{
			model = it_model->second;
			shaderComponent = dynamic_cast<ShaderComponent*>(components.find("Shader")->second);
			for (uint32 i = 0; i < shaders_p.size(); i++)
			{
				shaderComponent->AddShader(shaders_p [i]);
			}

			for (std::pair<std::string, ShaderNode*> it_shader : shaderComponent->GetShaders())
			{
				if (it_shader.second->isLoading)
				{
					it_shader.second->shader->Use();
					//it_shader.second->shader->SetMat4("projection", projection_p);
					//it_shader.second->shader->SetMat4("view", view_p);
					it_shader.second->shader->SetMat4("model", model_p);
					model->Draw(*(it_shader.second->shader));
				}
			}
		}
	}

	bool Object::HasComponent(const std::string& componentName_p) const
	{
		for (const std::pair<const std::string, Component*>& it_component : components)
		{
			if (it_component.second->GetName() == componentName_p)
			{
				return true;
			}
		}

		return false;
	}

	std::unordered_map<std::string, Component*> Object::GetComponents()
	{
		return components;
	}

	template<typename TComponent>
	TComponent* Object::TryGetComponent(const std::string& componentName_p)
	{
		for (Component& component : components)
		{
			if (component.GetName() == componentName_p)
			{
				return component;
			}
		}
	}

	/*template<typename TComponent>
	const TComponent* Object::TryGetComponentConst(const std::string& componentName) const
	{

	}*/

	void Object::SetPosition(const vec3f& position_p)
	{
		TransformComponent* transformComponent = dynamic_cast<TransformComponent*>(components.find("Transform")->second);
		transformComponent->SetPosition(position_p);
	}

	void Object::SetRotation(const vec3f& rotation_p)
	{
		TransformComponent* transformComponent = dynamic_cast<TransformComponent*>(components.find("Transform")->second);
		transformComponent->SetRotation(rotation_p);
	}

	void Object::SetScale(const vec3f& scale_p)
	{
		TransformComponent* transformComponent = dynamic_cast<TransformComponent*>(components.find("Transform")->second);
		transformComponent->SetScale(scale_p);
	}

	vec3f Object::GetPosition() const
	{
		TransformComponent* transformComponent = dynamic_cast<TransformComponent*>(components.find("Transform")->second);
		return transformComponent->GetPosition();
	}

	vec3f Object::GetRotation() const
	{
		TransformComponent* transformComponent = dynamic_cast<TransformComponent*>(components.find("Transform")->second);
		return transformComponent->GetRotation();
	}

	vec3f Object::GetScale() const
	{
		TransformComponent* transformComponent = dynamic_cast<TransformComponent*>(components.find("Transform")->second);
		return transformComponent->GetScale();
	}

	vec3f Object::GetFront() const
	{
		TransformComponent* transformComponent = dynamic_cast<TransformComponent*>(components.find("Transform")->second);
		return transformComponent->GetFront();
	}

	vec3f Object::GetRight() const
	{
		TransformComponent* transformComponent = dynamic_cast<TransformComponent*>(components.find("Transform")->second);
		return transformComponent->GetRight();
	}

	vec3f Object::GetUp() const
	{
		TransformComponent* transformComponent = dynamic_cast<TransformComponent*>(components.find("Transform")->second);
		return transformComponent->GetUp();
	}
}