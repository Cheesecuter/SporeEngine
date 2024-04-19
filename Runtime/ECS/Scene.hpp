#pragma once

#include <Types.hpp>
#include <Object.hpp>
#include <ModelObject.hpp>
#include <Light.hpp>
#include <Plane.hpp>
#include <PhysicSyetemHeaders.h>
#include <Layers.hpp>
#include <ObjectObserver.hpp>

namespace Spore
{
	class Scene : public ObjectObserver
	{
	public:
		Scene(std::string p_identifier);
		~Scene();

		std::string m_identifier;
		std::map<std::string, Object*> m_object_mapper;
		vec4f m_enviroment_color = vec4f(0.725f, 0.725f, 0.725f, 1.0f);
		int m_object_index = 0;
		bool m_flag_run = false;
		bool m_flag_stop = true;
		double step = 0;

		JPH::JobSystem* m_job_system = nullptr;
		JPH::PhysicsSystem* m_physics_system = nullptr;
		JPH::BodyInterface* m_body_interface = nullptr;
		JPH::TempAllocator* m_temp_allocator = nullptr;

		void AddObject(Object* p_object);
		void DeleteObject(Object* p_object);
		void DeleteObject(std::string p_identifier);
		void OnObjectDeleted(Object* p_object) override;
		void Render(std::vector<Shader*> p_shaders, Camera* p_camera,
					uint32 p_screen_width, uint32 p_screen_height,
					mat4f p_projection, mat4f p_view, mat4f p_model, 
					float32 p_delta_time);

		void InitPhysics();
		virtual void SetPhysicsSystem(JPH::PhysicsSystem* p_physics_system);
		void SetJobSystem(JPH::JobSystem* p_job_system);
		void SetTempAllocator(JPH::TempAllocator* p_temp_allocator);
		JPH::BodyInterface* GetBodyInterface();
		JPH::ContactListener* GetContactListener();
		JPH::Body& CreateFloor(float32 p_size = 200.0f);
		void Tick(uint32 step);
		void Active();

	private:
		class Listener : public JPH::BodyActivationListener
		{
		public:
			virtual void OnBodyActivated(const JPH::BodyID& p_body_ID, uint64 p_body_user_data) override
			{
				JPH::Trace("Body %d activated", p_body_ID.GetIndex());
			}

			virtual void OnBodyDeactivated(const JPH::BodyID& p_body_ID, uint64 p_body_user_data) override
			{
				JPH::Trace("Body %d deactivated", p_body_ID.GetIndex());
			}
		};

		Listener m_body_activation_listener;
	};
}
