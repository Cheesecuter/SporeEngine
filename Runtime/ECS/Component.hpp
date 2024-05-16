#pragma once

#include <Types.hpp>
#include <IMGUI_GLFW_OPENGL3.hpp>

namespace Spore
{
	class Object;

	class Component
	{
	public:
		Component() = default;
		virtual ~Component();

	public:

	protected:
		std::string m_name = "";
		Object* m_referenced_object = nullptr;
		bool m_is_dirty { false };
		bool m_is_scale_dirty { false };

	private:

	public:
		bool IsDirty() const;
		void SetDirtyFlag(bool p_is_dirty);
		/**
		 * @brief Get the name of the component.
		 *
		 * This function returns the name of the component.
		 *
		 * @return The name of the component.
		 */
		std::string GetName() const;
		/**
		 * @brief Set the referenced object for the component.
		 *
		 * This function sets the referenced object for the component.
		 *
		 * @param p_object Pointer to the object to be referenced.
		 */
		void SetReferencedObject(Object* p_object);
		/**
		 * @brief Get the referenced object of the component.
		 *
		 * This function returns a pointer to the object referenced by the component.
		 *
		 * @return Pointer to the referenced object.
		 */
		Object* GetReferencedObject();
		/**
		 * @brief Display the inspector panel for the component.
		 *
		 * This function is responsible for displaying the inspector panel for the component.
		 * Including UI elements to modify component properties.
		 */
		virtual void InspectorPanel();
		/**
		 * @brief Perform component update in each frame.
		 *
		 * This function is called in each frame to update the component.
		 *
		 * @param p_delta_time The time elapsed since the last frame.
		 */
		virtual void Tick(float32 p_delta_time);

	protected:

	private:

	};
}
