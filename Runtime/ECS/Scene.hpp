#pragma once

#include <Types.hpp>
#include <Object.hpp>
#include <ModelObject.hpp>
#include <Light.hpp>
#include <PhysicSyetemHeaders.h>
#include <Layers.hpp>
#include <ObjectObserver.hpp>
#include <ConsoleLogger.hpp>

namespace Spore
{
	class Scene : public ObjectObserver
	{
	public:
		Scene(std::string p_identifier);
		~Scene();

	public:
		std::string m_identifier;
		std::map<std::string, Object*> m_object_mapper;
		vec4f m_enviroment_color = vec4f(0.725f, 0.725f, 0.725f, 1.0f);
		int m_object_index = 0;
		bool m_flag_run = false;
		bool m_flag_stop = true;
		double step = 0;
		float32 m_delta_time_factor = 10.0f;
		Camera* m_editor_camera = nullptr;
		Camera* m_player_camera = nullptr;
		JPH::JobSystem* m_job_system = nullptr;
		JPH::PhysicsSystem* m_physics_system = nullptr;
		JPH::BodyInterface* m_body_interface = nullptr;
		JPH::TempAllocator* m_temp_allocator = nullptr;

	protected:

	private:

	public:
		/**
		 * @brief Add an object to the scene.
		 *
		 * This function adds an object to the scene and handles specific operations based on the object type.
		 * For Model objects, it sets up physics components and adds them to the physics system.
		 *
		 * @param p_object Pointer to the object to be added to the scene.
		 */
		void AddObject(Object* p_object);
		/**
		 * @brief Get an object from the scene by UUID.
		 *
		 * This function retrieves an object from the scene based on its UUID (Universally Unique Identifier).
		 *
		 * @param p_uuid The UUID of the object to retrieve.
		 * @return Pointer to the object if found, nullptr otherwise.
		 */
		Object* GetObjectByUUID(UUID p_uuid);
		/**
		 * @brief Get an object from the scene by name.
		 *
		 * This function retrieves an object from the scene based on its name.
		 *
		 * @param p_name The name of the object to retrieve.
		 * @return Pointer to the object if found, nullptr otherwise.
		 */
		Object* GetObjectByName(std::string p_name);
		/**
		 * @brief Delete an object from the scene.
		 *
		 * This function removes an object from the scene based on its identifier.
		 *
		 * @param p_object Pointer to the object to be deleted from the scene.
		 */
		void DeleteObject(Object* p_object);
		/**
		 * @brief Delete an object from the scene by identifier.
		 *
		 * This function removes an object from the scene based on its identifier.
		 *
		 * @param p_identifier The identifier of the object to be deleted from the scene.
		 */
		void DeleteObject(std::string p_identifier);
		/**
		 * @brief Handle object deletion notification.
		 *
		 * This function is called when an object is deleted.
		 * It removes the object from the scene's object mapper.
		 *
		 * @param p_object Pointer to the object that has been deleted.
		 */
		void OnObjectDeleted(Object* p_object) override;
		void Render(Camera* p_camera,
					uint32 p_screen_width, uint32 p_screen_height,
					float32 p_delta_time);
		/**
		 * @brief Initialize physics for the scene.
		 *
		 * This function initializes physics for the scene by setting up the body activation listener.
		 */
		void InitPhysics();
		/**
		 * @brief Set the physics system for the scene.
		 *
		 * This function sets the physics system and the body interface for the scene.
		 *
		 * @param p_physics_system Pointer to the physics system to be set for the scene.
		 */
		virtual void SetPhysicsSystem(JPH::PhysicsSystem* p_physics_system);
		/**
		 * @brief Set the job system for the scene.
		 *
		 * This function sets the job system to be used by the scene.
		 *
		 * @param p_job_system Pointer to the job system to be set for the scene.
		 */
		void SetJobSystem(JPH::JobSystem* p_job_system);
		/**
		 * @brief Set the temporary allocator for the scene.
		 *
		 * This function sets the temporary allocator to be used by the scene.
		 *
		 * @param p_temp_allocator Pointer to the temporary allocator to be set for the scene.
		 */
		void SetTempAllocator(JPH::TempAllocator* p_temp_allocator);
		/**
		 * @brief Get the body interface used by the scene.
		 *
		 * This function retrieves the body interface used by the scene for physics simulation.
		 *
		 * @return Pointer to the body interface used by the scene.
		 */
		JPH::BodyInterface* GetBodyInterface();
		/**
		 * @brief Get the contact listener used by the scene.
		 *
		 * This function retrieves the contact listener used by the scene for handling contacts between bodies.
		 *
		 * @return Pointer to the contact listener used by the scene, or nullptr if not set.
		 */
		JPH::ContactListener* GetContactListener();
		/**
		 * @brief Activate the scene.
		 *
		 * This function activates the scene by activating physics bodies associated with model objects.
		 */
		void Active();
		JPH::Body& CreateFloor(float32 p_size = 200.0f);
		void Tick(uint32 step);

	protected:

	private:
		class Listener : public JPH::BodyActivationListener
		{
		public:
			virtual void OnBodyActivated(const JPH::BodyID& p_body_ID, uint64 p_body_user_data) override
			{
				ConsoleLogger::GetInstance().Logger()->info("Body {} activated", p_body_ID.GetIndex());
			}

			virtual void OnBodyDeactivated(const JPH::BodyID& p_body_ID, uint64 p_body_user_data) override
			{
				ConsoleLogger::GetInstance().Logger()->info("Body {} deactivated", p_body_ID.GetIndex());
			}
		};
		Listener m_body_activation_listener;
	};
}
