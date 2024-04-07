#pragma once

#include <PhysicSyetemHeaders.h>
#include <PhysicsSettings.h>
#include <ContactListenerImpl.hpp>
#include <PhysicsTest.hpp>
#include <Layers.hpp>
#include <Scene.hpp>

JPH_SUPPRESS_WARNINGS_STD_BEGIN
#include <chrono>
JPH_SUPPRESS_WARNINGS_STD_END

namespace Spore
{
	class PhysicSystem
	{
	public:
		PhysicSystem();
		~PhysicSystem();

		PhysicsTest* m_test = nullptr;

		void Init();
		void Terminate();
		bool Update(float32 p_delta_time);
		void Tick(uint32 step);
		void AddScene(Scene* p_scene);

		void SetRenderFrequency(float32 p_frequency)
		{
			m_requested_delta_time = 1.0f / p_frequency;
		}

	protected:

	private:
		int32 m_max_concurrent_jobs = std::thread::hardware_concurrency();
		float32 m_update_frequency = 60.0f;
		int32 m_collision_steps = 1;
		JPH::TempAllocator* m_temp_allocator = nullptr;
		JPH::JobSystem* m_job_system = nullptr;
		JPH::JobSystem* m_job_system_validating = nullptr;
		BPLayerInterfaceImpl m_broad_phase_layer_interface;
		ObjectVsBroadPhaseLayerFilterImpl m_object_vs_broad_phase_layer_filter;
		ObjectLayerPairFilterImpl m_object_vs_object_layer_filter;
		JPH::PhysicsSystem* m_physics_system = nullptr;
		ContactListenerImpl* m_contact_listener = nullptr;
		JPH::PhysicsSettings m_physics_settings;

		const JPH::RTTI* m_test_class = nullptr;
		bool m_install_contact_listener = false;
		bool m_record_state = false;
		bool m_check_determinism = false;

		uint32 m_step_number = 0;
		std::chrono::microseconds m_total_time { 0 };

		float32 m_requested_delta_time = 0.0f;

		void Start(PhysicsTest* p_test);
		void DrawPhysics();
		void StepPhysics(JPH::JobSystem* p_job_stream);
		
	};
}
