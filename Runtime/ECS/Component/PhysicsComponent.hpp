#pragma once

#include <Types.hpp>
#include <Component.hpp>
#include <Transform.hpp>
#include <PhysicSyetemHeaders.h>
#include <Layers.hpp>
#include <Texture.hpp>
#include <ModelType.hpp>

namespace Spore
{
	class PhysicsComponent : public Component
	{
	public:
		PhysicsComponent();
		virtual ~PhysicsComponent();

	public:

	protected:

	private:
		JPH::Body* m_body = nullptr;
		JPH::BodyCreationSettings* m_body_creation_settings = nullptr;
		JPH::BodyInterface* m_body_interface = nullptr;
		ModelType m_model_type = ModelType::NONE;
		mat4x4f m_transform;
		vec3f m_position = vec3f(0.0f, 0.0f, 0.0f);
		vec3f m_rotation = vec3f(0.0f, 0.0f, 0.0f);
		vec3f m_scale = vec3f(1.0f, 1.0f, 1.0f);
		JPH::EMotionType m_current_motion_type;
		vec3f m_linear_velocity = vec3f(0.0f, 0.0f, 0.0f);
		vec3f m_angular_velocity = vec3f(0.0f, 0.0f, 0.0f);
		vec3f m_velocity = vec3f(0.0f, 0.0f, 0.0f);
		float32 m_gravity_factor = 1.0f;
		float32 m_restitution = 0.0f;
		float32 m_friction = 0.2f;
		Texture* m_button_image_reset;

	public:
		/**
		 * @brief Display the inspector panel for the physics component.
		 *
		 * This function displays the inspector panel for the physics component using ImGui.
		 * It allows the user to adjust various physics properties such as motion type, velocity, gravity factor, restitution, and friction.
		 */
		virtual void InspectorPanel() override;
		/**
		 * @brief Update the physics component during each tick.
		 *
		 * This function is called during each tick to update the physics component.
		 * It retrieves the position, rotation, and velocity of the associated body and updates internal variables accordingly.
		 *
		 * @param p_delta_time The time elapsed since the last tick.
		 */
		virtual void Tick(float32 p_delta_time) override;
		/**
		 * @brief Set the body creation settings for the physics component.
		 *
		 * This function sets the body creation settings for the physics component, including shape, position, rotation, motion type, and object layer.
		 * It also handles setting default shapes based on the model type if the provided shape is nullptr.
		 *
		 * @param p_shape The shape of the body.
		 * @param p_position The position of the body.
		 * @param p_rotation The rotation of the body.
		 * @param p_motion_type The motion type of the body.
		 * @param p_object_layer The object layer of the body.
		 */
		void SetBodyCreationSettings(const JPH::Shape* p_shape, 
									 JPH::RVec3 p_position, 
									 JPH::Quat p_rotation,
									 JPH::EMotionType p_motion_type, 
									 JPH::ObjectLayer p_object_layer);
		/**
		 * @brief Create and add the body to the physics simulation.
		 *
		 * This function creates the body using the stored body creation settings and adds it to the physics simulation.
		 */
		void CreateAndAddBody();
		/**
		 * @brief Get the body associated with this physics component.
		 *
		 * @return Pointer to the body.
		 */
		JPH::Body* GetBody();
		/**
		 * @brief Set the body interface for the physics component.
		 *
		 * @param p_body_interface Pointer to the body interface.
		 */
		void SetBodyInterface(JPH::BodyInterface* p_body_interface);
		/**
		 * @brief Get the body interface associated with this physics component.
		 *
		 * @return Pointer to the body interface.
		 */
		JPH::BodyInterface* GetBodyInterface();
		/**
		 * @brief Set the model type for the physics component.
		 *
		 * @param p_model_type The model type to set.
		 */
		void SetModelType(ModelType p_model_type);
		/**
		 * @brief Get the model type associated with this physics component.
		 *
		 * @return The model type.
		 */
		ModelType GetModelType();
		/**
		 * @brief Set the position of the body.
		 *
		 * @param p_position The position to set.
		 */
		void SetPosition(const vec3f& p_potision);
		/**
		 * @brief Get the position of the body.
		 *
		 * @return The position of the body.
		 */
		vec3f GetPosition();
		/**
		 * @brief Set the rotation of the body.
		 *
		 * @param p_rotation The rotation to set.
		 */
		void SetRotation(const vec3f& p_rotation);
		/**
		 * @brief Get the rotation of the body.
		 *
		 * @return The rotation of the body.
		 */
		vec3f GetRotation();
		//void SetScale(const vec3f& p_scale);
		//vec3f GetScale();

		/**
		 * @brief Set the transform of the body.
		 *
		 * @param p_transform The transform to set.
		 */
		void SetTransform(const Transform p_transform);
		/**
		 * @brief Get the transform of the body.
		 *
		 * @return The transform of the body.
		 */
		mat4x4f GetTransform();
		/**
		 * @brief Set the linear velocity of the body.
		 *
		 * @param p_velocity The linear velocity to set.
		 */
		void SetLinearVelocity(vec3f p_velocity);
		/**
		 * @brief Set the linear velocity of the body.
		 *
		 * @param p_x The x-component of the linear velocity.
		 * @param p_y The y-component of the linear velocity.
		 * @param p_z The z-component of the linear velocity.
		 */
		void SetLinearVelocity(float32 p_x, float32 p_y, float32 p_z);
		/**
		 * @brief Get the linear velocity of the body.
		 *
		 * @return The linear velocity of the body.
		 */
		vec3f GetLinearVelocity();
		/**
		 * @brief Set the angular velocity of the body.
		 *
		 * @param p_velocity The angular velocity to set.
		 */
		void SetAngularVelocity(vec3f p_velocity);
		/**
		 * @brief Set the angular velocity of the body.
		 *
		 * @param p_x The x-component of the angular velocity.
		 * @param p_y The y-component of the angular velocity.
		 * @param p_z The z-component of the angular velocity.
		 */
		void SetAngularVelocity(float32 p_x, float32 p_y, float32 p_z);
		/**
		 * @brief Get the angular velocity of the body.
		 *
		 * @return The angular velocity of the body.
		 */
		vec3f GetAngularVelocity();
		/**
		 * @brief Set the gravity factor of the body.
		 *
		 * @param p_gravity_factor The gravity factor to set.
		 */
		void SetGravityFactor(float32 p_gravity_factor);
		/**
		 * @brief Get the gravity factor of the body.
		 *
		 * @return The gravity factor of the body.
		 */
		float32 GetGravityFactor();
		/**
		 * @brief Set the restitution of the body.
		 *
		 * @param p_restitution The restitution to set.
		 */
		void SetRestitution(float32 p_restitution);
		/**
		 * @brief Get the restitution of the body.
		 *
		 * @return The restitution of the body.
		 */
		float32 GetRestitution();
		/**
		 * @brief Set the friction of the body.
		 *
		 * @param p_friction The friction to set.
		 */
		void SetFriction(float32 p_friction);
		/**
		 * @brief Get the friction of the body.
		 *
		 * @return The friction of the body.
		 */
		float32 GetFriction();
		/**
		 * @brief Wake up the body if it's not already active.
		 *
		 * @return True if the body was activated, false otherwise.
		 */
		bool Wake();

	protected:

	private:

	};
}