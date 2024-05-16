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

	public:

	protected:

	private:
		float m_ambient_ratio = 0.5f;
		Shader* m_lighting_shader = nullptr;
	
	public:
		/**
		 * @brief Render the inspector panel for the light component.
		 *
		 * This function renders the inspector panel for the light component using ImGui.
		 * It allows users to modify the ambient light ratio.
		 */
		virtual void InspectorPanel() override;
		/**
		 * @brief Set the lighting shader for the light component.
		 *
		 * This function sets the lighting shader used by the light component for rendering.
		 *
		 * @param p_shader Pointer to the lighting shader to set.
		 */
		void SetLightingShader(Shader* p_shader);
		/**
		 * @brief Get the lighting shader used by the light component.
		 *
		 * @return Pointer to the lighting shader used by the light component.
		 */
		Shader* GetLightingShader();
		/**
		 * @brief Render the light component.
		 *
		 * This function renders the light component using the specified camera, projection, view, and model matrices, and light position.
		 *
		 * @param p_camera Pointer to the camera used for rendering.
		 * @param p_projection The projection matrix.
		 * @param p_view The view matrix.
		 * @param p_model The model matrix.
		 * @param p_light_pos The position of the light source.
		 */
		void Render(Camera* p_camera, 
					mat4f p_projection, mat4f p_view, mat4f p_model, 
					vec3f p_light_pos);

	protected:

	private:

	};
}