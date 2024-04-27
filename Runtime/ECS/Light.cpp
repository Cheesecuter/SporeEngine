#include <Light.hpp>

namespace Spore
{
	Light::Light(const std::string& p_identifier) : Object(p_identifier, true)
	{
		m_type = "Light";
		ShaderComponent* shaderComponent = new ShaderComponent();
		//Shader* lightingShader = AssetsManager::GetInstance().m_shader_mapper.find("LightingFragment.glsl")->second;
		Shader* modelShader = AssetsManager::GetInstance().m_shader_mapper.find("ModelLoadingFragment.glsl")->second;
		//shaderComponent->AddShader(lightingShader);
		//shaderComponent->AddShader(lightingShader);
		LightComponent* lightComponent = new LightComponent();
		AddComponent(shaderComponent);
		AddComponent(lightComponent);
		Model* model = new Model("./Assets/Models/_basic models/cube.fbx");
		m_model_mapper.insert(std::make_pair(model->m_identifier, model));
	}

	Light::~Light()
	{

	}

	vec3f Light::GetLightColor()
	{
		return m_light_color;
	}

	void Light::Render(Camera* p_camera, uint32 p_screen_width, uint32 p_screen_height)
	{
		mat4f projectionM = glm::perspective(glm::radians(p_camera->m_zoom),
										(float32) p_screen_width / (float32) p_screen_height, 0.1f, 100.0f);
		mat4f viewM = p_camera->GetViewMatrix();

		TransformComponent* transformComponent = dynamic_cast<TransformComponent*>(m_components.find("Transform")->second);
		ShaderComponent* shaderComponent = dynamic_cast<ShaderComponent*>(m_components.find("Shader")->second);
		mat4f modelM = transformComponent->GetMatrix();

		LightComponent* lightComponent = dynamic_cast<LightComponent*>(m_components.find("Light")->second);
		lightComponent->Render(p_camera, projectionM, viewM, modelM, transformComponent->GetPosition());
	}

}