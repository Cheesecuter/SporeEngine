#include <PhysicsTest.hpp>

namespace Spore
{
	PhysicsTest::~PhysicsTest()
	{

	}

	void PhysicsTest::SetPhysicsSystem(JPH::PhysicsSystem* p_physics_system)
	{
		m_physics_system = p_physics_system;
		m_body_interface = &p_physics_system->GetBodyInterface();
	}

	void PhysicsTest::SetJobSystem(JPH::JobSystem* p_job_system)
	{
		m_job_system = p_job_system;
	}

	void PhysicsTest::SetTempAllocator(JPH::TempAllocator* p_temp_allocator)
	{
		m_temp_allocator = p_temp_allocator;
	}

	void PhysicsTest::Init()
	{

	}

	float32 PhysicsTest::GetWorldScale() const
	{
		return 1.0f;
	}

	JPH::ContactListener* PhysicsTest::GetContactListener()
	{
		return nullptr;
	}

	JPH::BodyInterface* PhysicsTest::GetBodyInterface()
	{
		return m_body_interface;
	}

	bool PhysicsTest::IsActive()
	{
		return false;
	}

	void PhysicsTest::Tick(uint32 step)
	{

	}

	JPH::Body& PhysicsTest::CreateFloor(float32 p_size)
	{
		const float scale = GetWorldScale();

		JPH::Body& floor = *m_body_interface->CreateBody(
			JPH::BodyCreationSettings(
				new JPH::BoxShape(scale * JPH::Vec3(0.5f * p_size, 1.0f, 0.5f * p_size), 0.0f), 
				JPH::RVec3(scale * JPH::Vec3(0.0f, -1.0f, 0.0f)), 
				JPH::Quat::sIdentity(), JPH::EMotionType::Static, Layers::NON_MOVING));
		m_body_interface->AddBody(floor.GetID(), JPH::EActivation::DontActivate);
		return floor;
	}

	JPH::Body& PhysicsTest::CreateLargeTriangleFloor()
	{
		JPH::TriangleList triangles = {
		   JPH::Triangle(JPH::Float3(427.941376f, 0.000027f, -456.470642f), JPH::Float3(427.941376f, 0.000024f, -399.411774f), JPH::Float3(512.0f, 0.000031f, -511.999969f)),
		   JPH::Triangle(JPH::Float3(0.0f, 0.000031f, -511.999969f), JPH::Float3(28.529310f, 0.000027f, -456.470642f), JPH::Float3(427.941376f, 0.000027f, -456.470642f)),
		   JPH::Triangle(JPH::Float3(427.941376f, 0.000027f, -456.470642f), JPH::Float3(512.0f, 0.000031f, -511.999969f), JPH::Float3(0.0f, 0.000031f, -511.999969f)),
		   JPH::Triangle(JPH::Float3(285.294067f, 0.000027f, -456.470642f), JPH::Float3(399.411804f, 0.000024f, -399.411774f), JPH::Float3(313.823395f, 0.000027f, -456.470642f)),
		   JPH::Triangle(JPH::Float3(313.823395f, 0.000027f, -456.470642f), JPH::Float3(399.411804f, 0.000024f, -399.411774f), JPH::Float3(342.352936f, 0.000027f, -456.470642f)),
		   JPH::Triangle(JPH::Float3(342.352936f, 0.000027f, -456.470642f), JPH::Float3(399.411804f, 0.000024f, -399.411774f), JPH::Float3(370.882507f, 0.000027f, -456.470642f)),
		   JPH::Triangle(JPH::Float3(399.411804f, 0.000024f, -399.411774f), JPH::Float3(427.941376f, 0.000024f, -399.411774f), JPH::Float3(370.882507f, 0.000027f, -456.470642f)),
		   JPH::Triangle(JPH::Float3(370.882507f, 0.000027f, -456.470642f), JPH::Float3(427.941376f, 0.000024f, -399.411774f), JPH::Float3(399.411804f, 0.000027f, -456.470642f)),
		   JPH::Triangle(JPH::Float3(399.411804f, 0.000027f, -456.470642f), JPH::Float3(427.941376f, 0.000024f, -399.411774f), JPH::Float3(427.941376f, 0.000027f, -456.470642f)),
		   JPH::Triangle(JPH::Float3(256.764771f, 0.000027f, -456.470642f), JPH::Float3(399.411804f, 0.000024f, -399.411774f), JPH::Float3(285.294067f, 0.000027f, -456.470642f)),
		   JPH::Triangle(JPH::Float3(85.588173f, 0.000027f, -456.470642f), JPH::Float3(399.411804f, 0.000024f, -399.411774f), JPH::Float3(114.117729f, 0.000027f, -456.470642f)),
		   JPH::Triangle(JPH::Float3(114.117729f, 0.000027f, -456.470642f), JPH::Float3(399.411804f, 0.000024f, -399.411774f), JPH::Float3(142.647034f, 0.000027f, -456.470642f)),
		   JPH::Triangle(JPH::Float3(142.647034f, 0.000027f, -456.470642f), JPH::Float3(399.411804f, 0.000024f, -399.411774f), JPH::Float3(171.176590f, 0.000027f, -456.470642f)),
		   JPH::Triangle(JPH::Float3(171.176590f, 0.000027f, -456.470642f), JPH::Float3(399.411804f, 0.000024f, -399.411774f), JPH::Float3(199.705902f, 0.000027f, -456.470642f)),
		   JPH::Triangle(JPH::Float3(199.705902f, 0.000027f, -456.470642f), JPH::Float3(399.411804f, 0.000024f, -399.411774f), JPH::Float3(228.235214f, 0.000027f, -456.470642f)),
		   JPH::Triangle(JPH::Float3(228.235214f, 0.000027f, -456.470642f), JPH::Float3(399.411804f, 0.000024f, -399.411774f), JPH::Float3(256.764771f, 0.000027f, -456.470642f)),
		   JPH::Triangle(JPH::Float3(85.588173f, 0.000024f, -399.411774f), JPH::Float3(399.411804f, 0.000024f, -399.411774f), JPH::Float3(85.588173f, 0.000027f, -456.470642f)),
		   JPH::Triangle(JPH::Float3(427.941376f, 0.000024f, -399.411774f), JPH::Float3(512.0f, 0.000019f, -313.823364f), JPH::Float3(512.0f, 0.000031f, -511.999969f)),
		   JPH::Triangle(JPH::Float3(399.411804f, 0.000024f, -399.411774f), JPH::Float3(512.0f, 0.000019f, -313.823364f), JPH::Float3(427.941376f, 0.000024f, -399.411774f)),
		   JPH::Triangle(JPH::Float3(285.294067f, 0.000024f, -399.411774f), JPH::Float3(512.0f, 0.000019f, -313.823364f), JPH::Float3(313.823395f, 0.000024f, -399.411774f)),
		   JPH::Triangle(JPH::Float3(313.823395f, 0.000024f, -399.411774f), JPH::Float3(512.0f, 0.000019f, -313.823364f), JPH::Float3(342.352936f, 0.000024f, -399.411774f)),
		   JPH::Triangle(JPH::Float3(342.352936f, 0.000024f, -399.411774f), JPH::Float3(512.0f, 0.000019f, -313.823364f), JPH::Float3(370.882507f, 0.000024f, -399.411774f)),
		   JPH::Triangle(JPH::Float3(370.882507f, 0.000024f, -399.411774f), JPH::Float3(512.0f, 0.000019f, -313.823364f), JPH::Float3(399.411804f, 0.000024f, -399.411774f)),
		   JPH::Triangle(JPH::Float3(256.764771f, 0.000024f, -399.411774f), JPH::Float3(512.0f, 0.000019f, -313.823364f), JPH::Float3(285.294067f, 0.000024f, -399.411774f)),
		   JPH::Triangle(JPH::Float3(228.235214f, 0.000024f, -399.411774f), JPH::Float3(512.0f, 0.000019f, -313.823364f), JPH::Float3(256.764771f, 0.000024f, -399.411774f)),
		   JPH::Triangle(JPH::Float3(199.705902f, 0.000024f, -399.411774f), JPH::Float3(512.0f, 0.000019f, -313.823364f), JPH::Float3(228.235214f, 0.000024f, -399.411774f)),
		   JPH::Triangle(JPH::Float3(228.235214f, 0.000019f, -313.823364f), JPH::Float3(512.0f, 0.000019f, -313.823364f), JPH::Float3(199.705902f, 0.000024f, -399.411774f)),
		   JPH::Triangle(JPH::Float3(142.647034f, 0.000024f, -399.411774f), JPH::Float3(228.235214f, 0.000019f, -313.823364f), JPH::Float3(171.176590f, 0.000024f, -399.411774f)),
		   JPH::Triangle(JPH::Float3(171.176590f, 0.000024f, -399.411774f), JPH::Float3(228.235214f, 0.000019f, -313.823364f), JPH::Float3(199.705902f, 0.000024f, -399.411774f)),
		   JPH::Triangle(JPH::Float3(85.588173f, 0.000022f, -370.882477f), JPH::Float3(228.235214f, 0.000019f, -313.823364f), JPH::Float3(142.647034f, 0.000024f, -399.411774f)),
		   JPH::Triangle(JPH::Float3(85.588173f, 0.000022f, -370.882477f), JPH::Float3(199.705902f, 0.000019f, -313.823364f), JPH::Float3(228.235214f, 0.000019f, -313.823364f)),
		   JPH::Triangle(JPH::Float3(114.117729f, 0.000024f, -399.411774f), JPH::Float3(85.588173f, 0.000022f, -370.882477f), JPH::Float3(142.647034f, 0.000024f, -399.411774f)),
		   JPH::Triangle(JPH::Float3(85.588173f, 0.000024f, -399.411774f), JPH::Float3(85.588173f, 0.000022f, -370.882477f), JPH::Float3(114.117729f, 0.000024f, -399.411774f)),
		   JPH::Triangle(JPH::Float3(28.529310f, 0.000019f, -313.823364f), JPH::Float3(199.705902f, 0.000019f, -313.823364f), JPH::Float3(85.588173f, 0.000022f, -370.882477f)),
		   JPH::Triangle(JPH::Float3(57.058865f, 0.000019f, -313.823364f), JPH::Float3(0.0f, 0.000017f, -285.294037f), JPH::Float3(85.588173f, 0.000019f, -313.823364f)),
		   JPH::Triangle(JPH::Float3(28.529310f, 0.000019f, -313.823364f), JPH::Float3(0.0f, 0.000017f, -285.294037f), JPH::Float3(57.058865f, 0.000019f, -313.823364f)),
		   JPH::Triangle(JPH::Float3(28.529310f, 0.000027f, -456.470642f), JPH::Float3(0.0f, 0.000017f, -285.294037f), JPH::Float3(57.058865f, 0.000027f, -456.470642f)),
		   JPH::Triangle(JPH::Float3(0.0f, 0.000017f, -285.294037f), JPH::Float3(28.529310f, 0.000027f, -456.470642f), JPH::Float3(0.0f, 0.000031f, -511.999969f)),
		   JPH::Triangle(JPH::Float3(0.0f, 0.000017f, -285.294037f), JPH::Float3(85.588173f, 0.000022f, -370.882477f), JPH::Float3(85.588173f, 0.000024f, -399.411774f)),
		   JPH::Triangle(JPH::Float3(0.0f, 0.000017f, -285.294037f), JPH::Float3(85.588173f, 0.000024f, -399.411774f), JPH::Float3(57.058865f, 0.000027f, -456.470642f)),
		   JPH::Triangle(JPH::Float3(57.058865f, 0.000027f, -456.470642f), JPH::Float3(85.588173f, 0.000024f, -399.411774f), JPH::Float3(85.588173f, 0.000027f, -456.470642f)),
		   JPH::Triangle(JPH::Float3(399.411804f, 0.000019f, -313.823364f), JPH::Float3(512.0f, 0.000003f, -57.058861f), JPH::Float3(456.470673f, 0.000019f, -313.823364f)),
		   JPH::Triangle(JPH::Float3(456.470673f, 0.000019f, -313.823364f), JPH::Float3(512.0f, 0.000003f, -57.058861f), JPH::Float3(512.0f, 0.000019f, -313.823364f)),
		   JPH::Triangle(JPH::Float3(228.235214f, 0.000019f, -313.823364f), JPH::Float3(512.0f, 0.000003f, -57.058861f), JPH::Float3(256.764771f, 0.000019f, -313.823364f)),
		   JPH::Triangle(JPH::Float3(256.764771f, 0.000019f, -313.823364f), JPH::Float3(512.0f, 0.000003f, -57.058861f), JPH::Float3(285.294067f, 0.000019f, -313.823364f)),
		   JPH::Triangle(JPH::Float3(285.294067f, 0.000019f, -313.823364f), JPH::Float3(512.0f, 0.000003f, -57.058861f), JPH::Float3(313.823395f, 0.000019f, -313.823364f)),
		   JPH::Triangle(JPH::Float3(313.823395f, 0.000019f, -313.823364f), JPH::Float3(512.0f, 0.000003f, -57.058861f), JPH::Float3(342.352936f, 0.000019f, -313.823364f)),
		   JPH::Triangle(JPH::Float3(342.352936f, 0.000019f, -313.823364f), JPH::Float3(512.0f, 0.000003f, -57.058861f), JPH::Float3(370.882507f, 0.000019f, -313.823364f)),
		   JPH::Triangle(JPH::Float3(370.882507f, 0.000019f, -313.823364f), JPH::Float3(512.0f, 0.000003f, -57.058861f), JPH::Float3(399.411804f, 0.000019f, -313.823364f)),
		   JPH::Triangle(JPH::Float3(0.0f, 0.000017f, -285.294037f), JPH::Float3(0.0f, 0.000009f, -142.647018f), JPH::Float3(512.0f, 0.000003f, -57.058861f)),
		   JPH::Triangle(JPH::Float3(199.705902f, 0.000019f, -313.823364f), JPH::Float3(512.0f, 0.000003f, -57.058861f), JPH::Float3(228.235214f, 0.000019f, -313.823364f)),
		   JPH::Triangle(JPH::Float3(171.176590f, 0.000019f, -313.823364f), JPH::Float3(512.0f, 0.000003f, -57.058861f), JPH::Float3(199.705902f, 0.000019f, -313.823364f)),
		   JPH::Triangle(JPH::Float3(0.0f, 0.000017f, -285.294037f), JPH::Float3(512.0f, 0.000003f, -57.058861f), JPH::Float3(85.588173f, 0.000019f, -313.823364f)),
		   JPH::Triangle(JPH::Float3(85.588173f, 0.000019f, -313.823364f), JPH::Float3(512.0f, 0.000003f, -57.058861f), JPH::Float3(142.647034f, 0.000019f, -313.823364f)),
		   JPH::Triangle(JPH::Float3(142.647034f, 0.000019f, -313.823364f), JPH::Float3(512.0f, 0.000003f, -57.058861f), JPH::Float3(171.176590f, 0.000019f, -313.823364f)),
		   JPH::Triangle(JPH::Float3(485.0f, 0.000002f, -28.529308f), JPH::Float3(512.0f, 0.0f, 0.0f), JPH::Float3(512.0f, 0.000002f, -28.529308f)),
		   JPH::Triangle(JPH::Float3(512.0f, 0.0f, 0.0f), JPH::Float3(427.941376f, 0.000002f, -28.529308f), JPH::Float3(285.294067f, 0.000002f, -28.529308f)),
		   JPH::Triangle(JPH::Float3(456.470673f, 0.000002f, -28.529308f), JPH::Float3(512.0f, 0.0f, 0.0f), JPH::Float3(485.0f, 0.000002f, -28.529308f)),
		   JPH::Triangle(JPH::Float3(427.941376f, 0.000002f, -28.529308f), JPH::Float3(512.0f, 0.0f, 0.0f), JPH::Float3(456.470673f, 0.000002f, -28.529308f)),
		   JPH::Triangle(JPH::Float3(171.176590f, 0.0f, 0.0f), JPH::Float3(512.0f, 0.0f, 0.0f), JPH::Float3(285.294067f, 0.000002f, -28.529308f)),
		   JPH::Triangle(JPH::Float3(285.294067f, 0.000002f, -28.529308f), JPH::Float3(512.0f, 0.000002f, -28.529308f), JPH::Float3(512.0f, 0.000003f, -57.058861f)),
		   JPH::Triangle(JPH::Float3(0.0f, 0.000009f, -142.647018f), JPH::Float3(285.294067f, 0.000002f, -28.529308f), JPH::Float3(512.0f, 0.000003f, -57.058861f)),
		   JPH::Triangle(JPH::Float3(0.0f, 0.000007f, -114.117722f), JPH::Float3(171.176590f, 0.0f, 0.0f), JPH::Float3(0.0f, 0.000009f, -142.647018f)),
		   JPH::Triangle(JPH::Float3(0.0f, 0.0f, 0.0f), JPH::Float3(171.176590f, 0.0f, 0.0f), JPH::Float3(0.0f, 0.000007f, -114.117722f)),
		   JPH::Triangle(JPH::Float3(0.0f, 0.000009f, -142.647018f), JPH::Float3(171.176590f, 0.0f, 0.0f), JPH::Float3(285.294067f, 0.000002f, -28.529308f))
		};
		JPH::MeshShapeSettings mesh_settings(triangles);
		mesh_settings.SetEmbedded();
		JPH::BodyCreationSettings floor_settings(&mesh_settings, JPH::RVec3(-256.0f, 0.0f, 256.0f), JPH::Quat::sIdentity(), JPH::EMotionType::Static, Layers::NON_MOVING);
		JPH::Body& floor = *m_body_interface->CreateBody(floor_settings);
		m_body_interface->AddBody(floor.GetID(), JPH::EActivation::DontActivate);
		return floor;
	}

	JPH::Body& PhysicsTest::CreateMeshTerrain()
	{
		JPH::Body* floor = nullptr;
		return *floor;
	}

	JPH::Body& PhysicsTest::CreateHeightFieldTerrian()
	{
		JPH::Body* floor = nullptr;
		return *floor;
	}

}