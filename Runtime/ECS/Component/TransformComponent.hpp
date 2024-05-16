#pragma once

#include <Types.hpp>
#include <Component.hpp>
#include <Transform.hpp>
#include <Texture.hpp>

namespace Spore
{
	class TransformComponent : public Component
	{
	public:
		TransformComponent();
		virtual ~TransformComponent();

	public:

	protected:
		Transform m_transform;
		Transform m_transformBuffer [2];
		uint64 m_currentIndex { 0 };
		uint64 m_nextIndex { 1 };
		Texture* m_button_image_reset;

	private:

	public:
		/**
		 * @brief Render the inspector panel for the transform component.
		 *
		 * This function renders the inspector panel for the transform component using ImGui.
		 * It allows users to modify the position, rotation, and scale of the transform.
		 */
		virtual void InspectorPanel() override;
		/**
		 * @brief Update the transform component's state.
		 *
		 * This function updates the transform component's position and rotation based on the physics component's state.
		 *
		 * @param p_delta_time The time elapsed since the last update.
		 */
		virtual void Tick(float32 p_delta_time) override;
		/**
		 * @brief Set the position of the transform component.
		 *
		 * This function sets the position of the transform component to the specified position vector.
		 *
		 * @param p_position The new position vector to set.
		 */
		void SetPosition(const vec3f& p_position);
		/**
		 * @brief Get the position of the transform component.
		 *
		 * This function retrieves the position of the transform component from the current transformation buffer.
		 *
		 * @return The position vector of the transform component.
		 */
		vec3f GetPosition() const;
		/**
		 * @brief Set the rotation of the transform component.
		 *
		 * This function sets the rotation of the transform component to the specified rotation vector.
		 *
		 * @param p_rotation The new rotation vector to set.
		 */
		void SetRotation(const vec3f& p_rotation);
		/**
		 * @brief Get the rotation of the transform component.
		 *
		 * This function retrieves the rotation of the transform component from the current transformation buffer.
		 *
		 * @return The rotation vector of the transform component.
		 */
		vec3f GetRotation() const;
		/**
		 * @brief Set the scale of the transform component.
		 *
		 * This function sets the scale of the transform component to the specified scale vector.
		 *
		 * @param p_scale The new scale vector to set.
		 */
		void SetScale(const vec3f& p_scale);
		/**
		 * @brief Get the scale of the transform component.
		 *
		 * This function retrieves the scale of the transform component from the current transformation buffer.
		 *
		 * @return The scale vector of the transform component.
		 */
		vec3f GetScale() const;
		/**
		 * @brief Get the front vector of the transform component.
		 *
		 * This function retrieves the front vector of the transform component from the current transformation buffer.
		 *
		 * @return The front vector of the transform component.
		 */
		vec3f GetFront() const;
		/**
		 * @brief Get the right vector of the transform component.
		 *
		 * This function retrieves the right vector of the transform component from the current transformation buffer.
		 *
		 * @return The right vector of the transform component.
		 */
		vec3f GetRight() const;
		/**
		 * @brief Get the up vector of the transform component.
		 *
		 * This function retrieves the up vector of the transform component from the current transformation buffer.
		 *
		 * @return The up vector of the transform component.
		 */
		vec3f GetUp() const;
		/**
		 * @brief Get the transformation matrix of the transform component.
		 *
		 * This function retrieves the transformation matrix of the transform component.
		 *
		 * @return The transformation matrix of the transform component.
		 */
		mat4x4f GetMatrix() const;

	protected:

	private:

	};
}
