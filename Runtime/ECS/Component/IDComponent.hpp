#pragma once

#include <Types.hpp>
#include <Component.hpp>
#include <UUID.hpp>

namespace Spore
{
	class IDComponent : public Component
	{
	public:
		IDComponent();
		virtual ~IDComponent();

	public:

	protected:

	private:
		UUID m_UUID;

	public:
		/**
		 * @brief Render the inspector panel for the ID component.
		 *
		 * This function renders the inspector panel for the ID component using ImGui.
		 * It displays the UUID associated with the component.
		 */
		virtual void InspectorPanel() override;
		/**
		 * @brief Set the UUID of the ID component.
		 *
		 * This function sets the UUID of the ID component to the specified value.
		 *
		 * @param p_uuid The UUID to set.
		 */
		void SetID(uint64 p_uuid);
		/**
		 * @brief Get the UUID of the ID component.
		 *
		 * @return The UUID of the ID component.
		 */
		UUID GetID();

	protected:

	private:

	};
}