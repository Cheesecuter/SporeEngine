#include <LightComponent.hpp>

namespace Spore
{
	LightComponent::LightComponent()
	{
		m_name = "Light";
		m_lighting_shader = AssetsManager::GetInstance().m_shader_mapper ["LightingFragment.glsl"];

		m_lighting_shader->Use();
		m_lighting_shader->SetFloat("ambientRatio", 0.5f);
	}

	LightComponent::~LightComponent()
	{

	}

	void LightComponent::InspectorPanel()
	{
		if (ImGui::CollapsingHeader(m_name.c_str(), true))
		{
			ImGui::Text("Ambient Light");
			ImGui::PushID("Inspector::Light::Ambient_Light");
			ImGui::DragFloat("##Inspector::Light::Ambient_Light", &m_ambient_ratio, 0.01f);
			ImGui::PopID();

			m_lighting_shader->Use();
			m_lighting_shader->SetFloat("ambientRatio", m_ambient_ratio);

		}
	}

	void LightComponent::SetLightingShader(Shader* p_shader)
	{
		m_lighting_shader = p_shader;
	}
	
	Shader* LightComponent::GetLightingShader()
	{
		return m_lighting_shader;
	}

	void LightComponent::Render(Camera* p_camera,
								mat4f p_projection, mat4f p_view, mat4f p_model,
								vec3f p_light_pos)
	{
		m_lighting_shader->Use();
		m_lighting_shader->SetMat4("projection", p_projection);
		m_lighting_shader->SetMat4("view", p_view);
		m_lighting_shader->SetMat4("model", p_model);
		m_lighting_shader->SetVec3("viewPos", p_camera->m_position);
		m_lighting_shader->SetVec3("lightPos", p_light_pos);
		m_lighting_shader->SetBool("blinn", true);
	}
}