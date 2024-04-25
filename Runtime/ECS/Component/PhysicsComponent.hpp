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
		virtual void InspectorPanel() override;
		virtual void Tick(float32 p_delta_time) override;
		void SetBodyCreationSettings(const JPH::Shape* p_shape, 
									 JPH::RVec3 p_position, 
									 JPH::Quat p_rotation,
									 JPH::EMotionType p_motion_type, 
									 JPH::ObjectLayer p_object_layer);
		void CreateAndAddBody();
		JPH::Body* GetBody();
		void SetBodyInterface(JPH::BodyInterface* p_body_interface);
		JPH::BodyInterface* GetBodyInterface();
		void SetModelType(ModelType p_model_type);
		ModelType GetModelType();
		void SetPosition(const vec3f& p_potision);
		vec3f GetPosition();
		void SetRotation(const vec3f& p_rotation);
		vec3f GetRotation();
		//void SetScale(const vec3f& p_scale);
		//vec3f GetScale();
		void SetTransform(const Transform p_transform);
		mat4x4f GetTransform();
		void SetLinearVelocity(vec3f p_velocity);
		void SetLinearVelocity(float32 p_x, float32 p_y, float32 p_z);
		vec3f GetLinearVelocity();
		void SetAngularVelocity(vec3f p_velocity);
		void SetAngularVelocity(float32 p_x, float32 p_y, float32 p_z);
		vec3f GetAngularVelocity();
		void SetGravityFactor(float32 p_gravity_factor);
		float32 GetGravityFactor();
		void SetRestitution(float32 p_restitution);
		float32 GetRestitution();
		void SetFriction(float32 p_friction);
		float32 GetFriction();
		bool Wake();

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
	};
}