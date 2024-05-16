#pragma once

#include <Types.hpp>
#include <Model.hpp>
#include <Shader.hpp>
#include <Camera.hpp>
#include <AssetsManager.hpp>
#include <UUID.hpp>
#include <Component.hpp>
#include <TransformComponent.hpp>
#include <ShaderComponent.hpp>
#include <ModelObserver.hpp>
#include <ObjectObserver.hpp>

namespace Spore
{
	class Object : public ModelObserver
	{
	public:
		Object(const std::string& p_identifier, const bool p_light = false);
		virtual ~Object();

	public:
		std::string m_identifier;
		std::string m_type = "Default";
		bool m_selected = false;

	protected:
		std::unordered_map<std::string, Component*> m_components;
		Shader* m_model_shader;

	private:
		std::vector<ObjectObserver*> m_observer_list;

	public:
		/**
		 * @brief Add an observer to the object.
		 *
		 * This function adds an observer to the object's observer list.
		 *
		 * @param p_observer Pointer to the observer to be added.
		 */
		void AddObserver(ObjectObserver* p_observer);
		/**
		 * @brief Remove an observer from the object.
		 *
		 * This function removes an observer from the object's observer list.
		 *
		 * @param p_observer Pointer to the observer to be removed.
		 */
		void RemoveObserver(ObjectObserver* p_observer);
		/**
		 * @brief Delete the object.
		 *
		 * This function notifies all observers that the object is being deleted.
		 * It calls the OnObjectDeleted method for each observer.
		 */
		void DeleteObject();
		void Update(float32 p_deltaTime);
		virtual void Render(Camera* p_camera, uint32 p_screen_width, uint32 p_screen_height);
		/**
		 * @brief Add a component to the object.
		 *
		 * This function adds a component to the object.
		 *
		 * @param p_component Pointer to the component to be added.
		 * @return True if the component is successfully added, false otherwise.
		 */
		bool AddComponent(Component* p_component);
		/**
		 * @brief Add a component to the object.
		 *
		 * This function adds a component to the object.
		 *
		 * @param p_component Pointer to the component to be added.
		 * @return True if the component is successfully added, false otherwise.
		 */
		bool HasComponent(const std::string& p_component_name) const;
		/**
		 * @brief Get the components of the object.
		 *
		 * This function returns a map containing the components of the object.
		 *
		 * @return Map containing components, where the key is the component name and the value is a pointer to the component.
		 */
		std::unordered_map<std::string, Component*> GetComponents();
		/**
		 * @brief Get a specific component of the object.
		 *
		 * This function returns a pointer to the component with the specified name.
		 *
		 * @param p_component_name The name of the component to retrieve.
		 * @return Pointer to the component, or nullptr if the component is not found.
		 */
		Component* GetComponent(const std::string& p_component_name);
		/**
		 * @brief Attempt to get a specific component of the object.
		 *
		 * This function attempts to retrieve a component of the specified type from the object's components.
		 *
		 * @tparam TComponent The type of component to retrieve.
		 * @param p_component_name The name of the component to retrieve.
		 * @return Pointer to the component of the specified type if found, nullptr otherwise.
		 */
		template<typename TComponent>
		TComponent* TryGetComponent(const std::string& p_component_name);
		/**
		 * @brief Get the UUID of the object.
		 *
		 * This function retrieves the UUID (Universally Unique Identifier) of the object, if available.
		 * It searches for an IDComponent named "UUID" in the object's components.
		 *
		 * @return The UUID of the object, or a default UUID if not found.
		 */
		UUID GetUUID();
		/**
		 * @brief Set the position of the object.
		 *
		 * This function sets the position of the object using the provided 3D vector.
		 * It retrieves the TransformComponent from the object's components and sets its position.
		 *
		 * @param p_position The new position of the object.
		 */
		void SetPosition(const vec3f& p_position);
		/**
		 * @brief Get the position of the object.
		 *
		 * This function retrieves the position of the object from its TransformComponent.
		 *
		 * @return The position of the object as a 3D vector.
		 */
		vec3f GetPosition() const;
		/**
		 * @brief Set the rotation of the object.
		 *
		 * This function sets the rotation of the object using the provided 3D vector.
		 * It retrieves the TransformComponent from the object's components and sets its rotation.
		 *
		 * @param p_rotation The new rotation of the object.
		 */
		void SetRotation(const vec3f& p_rotation);
		/**
		 * @brief Get the rotation of the object.
		 *
		 * This function retrieves the rotation of the object from its TransformComponent.
		 *
		 * @return The rotation of the object as a 3D vector.
		 */
		vec3f GetRotation() const;
		/**
		 * @brief Set the scale of the object.
		 *
		 * This function sets the scale of the object using the provided 3D vector.
		 * It retrieves the TransformComponent from the object's components and sets its scale.
		 *
		 * @param p_scale The new scale of the object.
		 */
		void SetScale(const vec3f& p_scale);
		/**
		 * @brief Get the scale of the object.
		 *
		 * This function retrieves the scale of the object from its TransformComponent.
		 *
		 * @return The scale of the object as a 3D vector.
		 */
		vec3f GetScale() const;
		/**
		 * @brief Get the front direction of the object.
		 *
		 * This function retrieves the front direction of the object from its TransformComponent.
		 *
		 * @return The front direction of the object as a 3D vector.
		 */
		vec3f GetFront() const;
		/**
		 * @brief Get the right direction of the object.
		 *
		 * This function retrieves the right direction of the object from its TransformComponent.
		 *
		 * @return The right direction of the object as a 3D vector.
		 */
		vec3f GetRight() const;
		/**
		 * @brief Get the up direction of the object.
		 *
		 * This function retrieves the up direction of the object from its TransformComponent.
		 *
		 * @return The up direction of the object as a 3D vector.
		 */
		vec3f GetUp() const;

	protected:

	private:

	};
}
