#pragma once

#include <Types.hpp>
#include <Component.hpp>
#include <Camera.hpp>
#include <Texture.hpp>

namespace Spore
{
	class CameraComponent : public Component
	{
	public:
		CameraComponent();
		virtual ~CameraComponent();

	public:

	protected:

	private:
		Camera* m_camera = nullptr;
		float32 m_x_offset = 3.0f;
		float32 m_y_offset = 3.0f;
		float32 m_z_offset = 3.0f;
		Texture* m_button_image_reset;

	public:
		/**
		 * @brief Render the inspector panel for the camera component.
		 *
		 * This function renders the inspector panel for the camera component using ImGui.
		 * It allows users to modify the camera offset.
		 */
		virtual void InspectorPanel() override;
		/**
		 * @brief Update the camera component's state.
		 *
		 * This function updates the camera component's position based on the position of the associated transform component.
		 *
		 * @param p_delta_time The time elapsed since the last update.
		 */
		virtual void Tick(float32 p_delta_time) override;
		/**
		 * @brief Set the camera object associated with the camera component.
		 *
		 * This function sets the camera object associated with the camera component.
		 *
		 * @param p_camera Pointer to the camera object to set.
		 */
		void SetCamera(Camera* p_camera);
		/**
		 * @brief Get the camera object associated with the camera component.
		 *
		 * @return Pointer to the camera object associated with the camera component.
		 */
		Camera* GetCamera();

	protected:

	private:

	};
}