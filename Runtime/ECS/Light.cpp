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

	void Light::Render(std::vector<Shader*> p_shaders, Camera* p_camera,
				uint32 p_screen_width, uint32 p_screen_height,
				mat4f p_projection, mat4f p_view, mat4f p_model)
	{
		p_projection = glm::perspective(glm::radians(p_camera->m_zoom),
										(float32) p_screen_width / (float32) p_screen_height, 0.1f, 100.0f);
		p_view = p_camera->GetViewMatrix();

		TransformComponent* transformComponent = dynamic_cast<TransformComponent*>(m_components.find("Transform")->second);
		ShaderComponent* shaderComponent = dynamic_cast<ShaderComponent*>(m_components.find("Shader")->second);
		p_model = transformComponent->GetMatrix();

		LightComponent* lightComponent = dynamic_cast<LightComponent*>(m_components.find("Light")->second);
		lightComponent->Render(p_camera, p_projection, p_view, p_model, transformComponent->GetPosition());
		/*for (std::pair<std::string, ShaderNode*> it_shader : shaderComponent->GetShaders())
		{
			it_shader.second->m_shader->Use();
			it_shader.second->m_shader->SetMat4("projection", p_projection);
			it_shader.second->m_shader->SetMat4("view", p_view);
			it_shader.second->m_shader->SetMat4("model", p_model);
			it_shader.second->m_shader->SetVec3("viewPos", p_camera->m_position);
			it_shader.second->m_shader->SetVec3("lightPos", transformComponent->GetPosition());
			it_shader.second->m_shader->SetInt("blinn", true);
		}*/
	}

}