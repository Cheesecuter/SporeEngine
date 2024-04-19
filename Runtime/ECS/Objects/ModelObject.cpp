#include <ModelObject.hpp>

namespace Spore
{
	ModelObject::ModelObject(const std::string& p_identifier) : Object(p_identifier)
	{
		m_type = "Model";
		m_model_mapper = std::map<std::string, Model*>();
		ModelComponent* modelComponent = new ModelComponent();
		AddComponent(modelComponent);
		ShaderComponent* shaderComponent = new ShaderComponent(); 
		//Shader* shader = AssetsManager::GetInstance().m_shader_mapper.find("ModelLoadingFragment.glsl")->second;
		Shader* shader = AssetsManager::GetInstance().m_shader_mapper.find("LightingFragment.glsl")->second;
		m_model_shader = shader;
		shaderComponent->AddShader(m_model_shader);
		//shaderComponent->AddShader(shader1);
		AddComponent(shaderComponent);

		PhysicsComponent* physicsComponent = new PhysicsComponent();
		AddComponent(physicsComponent);

		AudioComponent* audioComponent = new AudioComponent();
		AddComponent(audioComponent);
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
		ModelComponent* modelComponent = dynamic_cast<ModelComponent*>(m_components.find("Model")->second);
		modelComponent->AddModel(p_model);
	}

	Model* ModelObject::GetModel()
	{
		ModelComponent* modelComponent = dynamic_cast<ModelComponent*>(m_components.find("Model")->second);
		return modelComponent->GetModel();
	}

	void ModelObject::DeleteModel(Model* p_model)
	{
		ModelComponent* modelComponent = dynamic_cast<ModelComponent*>(m_components.find("Model")->second);
		modelComponent->DeleteModel(p_model->m_identifier);
	}

	void ModelObject::DeleteModel(std::string p_identifier)
	{
		ModelComponent* modelComponent = dynamic_cast<ModelComponent*>(m_components.find("Model")->second);
		modelComponent->DeleteModel(p_identifier);
	}

	void ModelObject::OnModelDeleted(Model* p_model)
	{

	}

	bool ModelObject::ModelMapperEmpty()
	{
		ModelComponent* modelComponent = dynamic_cast<ModelComponent*>(m_components.find("Model")->second);
		return modelComponent->GetModel() == nullptr;
	}

	void ModelObject::SetModelType(ModelType p_model_type)
	{
		ModelComponent* modelComponent = dynamic_cast<ModelComponent*>(m_components.find("Model")->second);
		modelComponent->SetModelType(p_model_type);
	}

	ModelType ModelObject::GetModelType()
	{
		ModelComponent* modelComponent = dynamic_cast<ModelComponent*>(m_components.find("Model")->second);
		return modelComponent->GetModelType();
	}

	void ModelObject::Render(std::vector<Shader*> p_shaders, Camera* p_camera,
						uint32 p_screen_width, uint32 p_screen_height,
						mat4f p_projection, mat4f p_view, mat4f p_model)
	{
		PhysicsComponent* physicsComponent = dynamic_cast<PhysicsComponent*>(m_components.find("Physics")->second);
		TransformComponent* transformComponent = dynamic_cast<TransformComponent*>(m_components.find("Transform")->second);
		p_projection = glm::perspective(glm::radians(p_camera->m_zoom),
										(float32) p_screen_width / (float32) p_screen_height, 0.1f, 10000.0f);
		p_view = p_camera->GetViewMatrix();
		p_model = transformComponent->GetMatrix();
		ModelComponent* modelComponent = dynamic_cast<ModelComponent*>(m_components.find("Model")->second);
		modelComponent->SetModelTransformMatrixNode(p_projection, p_view, p_model);
		ShaderComponent* shaderComponent = dynamic_cast<ShaderComponent*>(m_components.find("Shader")->second);
		transformComponent->Tick(10);
		physicsComponent->Tick(10);
		shaderComponent->Tick(10);
		modelComponent->Tick(10);
	}
}