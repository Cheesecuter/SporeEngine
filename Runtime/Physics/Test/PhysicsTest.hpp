#pragma once

#include <PhysicSyetemHeaders.h>
#include <Types.hpp>
#include <Layers.hpp>

namespace Spore
{
	class PhysicsTest
	{
	public:
		//JPH_DECLARE_RTTI_VIRTUAL_BASE(JPH_NO_EXPORT, PhysicsTest)

		virtual ~PhysicsTest();
		virtual void SetPhysicsSystem(JPH::PhysicsSystem* p_physics_system);
		void SetJobSystem(JPH::JobSystem* p_job_system);
		void SetTempAllocator(JPH::TempAllocator* p_temp_allocator);
		virtual void Init();
		virtual float32 GetWorldScale() const;
		virtual JPH::ContactListener* GetContactListener();
		JPH::BodyInterface* GetBodyInterface();
		virtual bool IsActive();
		virtual void Tick(uint32 step);

	protected:
		JPH::JobSystem* m_job_system = nullptr;
		JPH::PhysicsSystem* m_physics_system = nullptr;
		JPH::BodyInterface* m_body_interface = nullptr;
		JPH::TempAllocator* m_temp_allocator = nullptr;

		JPH::Body& CreateFloor(float32 p_size = 200.0f);
		JPH::Body& CreateLargeTriangleFloor();
		JPH::Body& CreateMeshTerrain();
		JPH::Body& CreateHeightFieldTerrian();

	private:
		
	};
}
