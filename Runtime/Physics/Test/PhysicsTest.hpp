#pragma once
#ifndef PHYSICS_TEST_HPP
#define PHYSICS_TEST_HPP

#include <JoltPhysics/Jolt/Jolt.h>
#include <JoltPhysics/Jolt/Physics/PhysicsSystem.h>
#include <JoltPhysics/Jolt/Physics/Body/BodyCreationSettings.h>
#include <JoltPhysics/Jolt/Physics/Collision/Shape/BoxShape.h>
#include <JoltPhysics/Jolt/Physics/Collision/Shape/MeshShape.h>
#include <JoltPhysics/Jolt/Physics/Collision/Shape/HeightFieldShape.h>
#include <JoltPhysics/Jolt/Core/RTTI.h>

#include <Types.hpp>
#include <Layers.hpp>

namespace Spore
{
	class PhysicsTest
	{
	public:
		virtual ~PhysicsTest();
		virtual void SetPhysicsSystem(JPH::PhysicsSystem* p_physics_system);
		void SetJobSystem(JPH::JobSystem* p_job_system);
		void SetTempAllocator(JPH::TempAllocator* p_temp_allocator);
		virtual void Init();
		virtual float32 GetWorldScale() const;
		virtual JPH::ContactListener* GetContactListener();

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

#endif
