#include <Light.hpp>

namespace Spore
{
	Light::Light(const std::string& identifier_p) : Object(identifier_p, true)
	{
		type = "light";
		ShaderComponent* shaderComponent = new ShaderComponent();
		Shader* lightingShader = AssetsManager::GetInstance().shaderMapper.find("LightingFragment.glsl")->second;
		Shader* modelShader = AssetsManager::GetInstance().shaderMapper.find("ModelLoadingFragment.glsl")->second;
		//shaderComponent->AddShader(lightingShader);
		shaderComponent->AddShader(modelShader);
		components [shaderComponent->GetName()] = shaderComponent;
		Model* model = new Model(std::string("./Assets/Models/cube.fbx"));
		modelMapper.insert(std::make_pair(model->identifier, model));
	}

	Light::~Light()
	{

	}

	vec3f Light::GetLightColor()
	{
		return lightColor;
	}

	void Light::Render(std::vector<Shader*> shaders_p, Camera* camera_p,
				uint32 scrWidth_p, uint32 scrHeight_p,
				mat4f projection_p, mat4f view_p, mat4f model_p)
	{
		projection_p = glm::perspective(glm::radians(camera_p->Zoom),
										(float32) scrWidth_p / (float32) scrHeight_p, 0.1f, 100.0f);
		view_p = camera_p->GetViewMatrix();

		TransformComponent* transformComponent = dynamic_cast<TransformComponent*>(components.find("Transform")->second);
		ShaderComponent* shaderComponent = dynamic_cast<ShaderComponent*>(components.find("Shader")->second);
		model_p = transformComponent->GetMatrix();

		for (std::pair<std::string, ShaderNode*> it_shader : shaderComponent->GetShaders())
		{
			it_shader.second->shader->Use();
			it_shader.second->shader->SetMat4("projection", projection_p);
			it_shader.second->shader->SetMat4("view", view_p);
			it_shader.second->shader->SetMat4("model", model_p);
			it_shader.second->shader->SetVec3("viewPos", camera_p->Position);
			it_shader.second->shader->SetVec3("lightPos", transformComponent->GetPosition());
			it_shader.second->shader->SetInt("blinn", true);
		}
	}

}