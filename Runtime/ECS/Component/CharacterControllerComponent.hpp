#pragma once

#include <Component.hpp>

namespace Spore
{
	class CharacterControllerComponent : public Component
	{
	public:
		CharacterControllerComponent();
		virtual ~CharacterControllerComponent();

	public:
		/**
		 * @brief Render the inspector panel for the character controller component.
		 *
		 * This function renders the inspector panel for the character controller component using ImGui.
		 * It provides information about the character controller.
		 */
		virtual void InspectorPanel() override;
		/**
		 * @brief Update the character controller component's state.
		 *
		 * This function updates the character controller component's state based on user input.
		 *
		 * @param p_delta_time The time elapsed since the last update.
		 */
		virtual void Tick(float32 p_delta_time) override;

	protected:

	private:

	};
}