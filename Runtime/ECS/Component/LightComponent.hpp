#pragma once

#include <Types.hpp>
#include <Component.hpp>
#include <Shader.hpp>
#include <AssetsManager.hpp>
#include <Camera.hpp>

namespace Spore
{
	class LightComponent : public Component
	{
	public:
		LightComponent();
		virtual ~LightComponent();

		virtual void InspectorPanel() override;
		void SetLightingShader(Shader* p_shader);
		Shader* GetLightingShader();
		void Render(Camera* p_camera, 
					mat4f p_projection, mat4f p_view, mat4f p_model, 
					vec3f p_light_pos);

	protected:

	private:
		float m_ambient_ratio = 0.5f;
		Shader* m_lighting_shader = nullptr;
	};
}