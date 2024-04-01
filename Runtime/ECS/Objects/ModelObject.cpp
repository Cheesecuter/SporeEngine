#include <ModelObject.hpp>

namespace Spore
{
	ModelObject::ModelObject(const std::string& identifier_p) : Object(identifier_p)
	{
		type = "model";
		modelMapper = std::map<std::string, Model*>();
		ShaderComponent* shaderComponent = new ShaderComponent();
		Shader* shader = AssetsManager::GetInstance().shaderMapper.find("ModelLoadingFragment.glsl")->second;
		modelShader = shader;
		shaderComponent->AddShader(modelShader);
		components [shaderComponent->GetName()] = shaderComponent;
	}

	ModelObject::~ModelObject()
	{
		components.clear();
		modelMapper.clear();
		DeleteObject();
	}

	void ModelObject::AddModel(Model* model_p)
	{
		std::shared_ptr<ModelObject> object = std::make_shared<ModelObject>(this->identifier);
		modelMapper.insert(std::make_pair(model_p->identifier, model_p));
		modelMapper [model_p->identifier]->AddObserver(object);
	}

	void ModelObject::DeleteModel(Model model_p)
	{
		modelMapper.erase(model_p.identifier);
	}

	void ModelObject::DeleteModel(std::string identifier_p)
	{
		modelMapper.erase(identifier_p);
	}

	void ModelObject::OnModelDeleted(Model* model)
	{
		modelMapper.erase(model->identifier);
		ModelObject::~ModelObject();
	}

	void ModelObject::Render(std::vector<Shader*> shaders_p, Camera* camera_p,
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
					it_shader.second->shader->SetBool("alphaFilterFlag", it_shader.second->shader->alphaFilterFlag);
					it_shader.second->shader->SetMat4("projection", projection_p);
					it_shader.second->shader->SetMat4("view", view_p);
					it_shader.second->shader->SetMat4("model", model_p);
					model->Draw(*(it_shader.second->shader));
				}
			}
		}
	}
}