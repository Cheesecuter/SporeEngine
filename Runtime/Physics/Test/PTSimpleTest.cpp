#include <PTSimpleTest.hpp>
#include <JoltPhysics/Jolt/Physics/Collision/Shape/BoxShape.h>
#include <JoltPhysics/Jolt/Physics/Collision/Shape/SphereShape.h>
#include <JoltPhysics/Jolt/Physics/Body/BodyCreationSettings.h>
#include <JoltPhysics/Jolt/Physics/Body/BodyActivationListener.h>
#include <Layers.hpp>

namespace Spore
{
	PTSimpleTest::~PTSimpleTest()
	{
		m_physics_system->SetBodyActivationListener(nullptr);
	}

	void PTSimpleTest::Init()
	{
		m_physics_system->SetBodyActivationListener(&m_body_activation_listener);

		CreateFloor();

		JPH::RefConst<JPH::Shape> box_shape = new JPH::BoxShape(JPH::Vec3(0.5f, 1.0f, 2.0f));
		JPH::RefConst<JPH::Shape> sphere_shape = new JPH::SphereShape(2.0f);

		JPH::Body& body1 = *m_body_interface->CreateBody(JPH::BodyCreationSettings(box_shape,
																				   JPH::RVec3(0, 10, 0),
																				   JPH::Quat::sIdentity(),
																				   JPH::EMotionType::Dynamic,
																				   Layers::MOVING));
		m_body_interface->AddBody(body1.GetID(), JPH::EActivation::Activate);

		JPH::Body& body2 = *m_body_interface->CreateBody(JPH::BodyCreationSettings(box_shape,
																				   JPH::RVec3(5, 10, 0),
																				   JPH::Quat::sRotation(JPH::Vec3::sAxisX(), 0.25f * PI),
																				   JPH::EMotionType::Dynamic,
																				   Layers::MOVING));
		m_body_interface->AddBody(body2.GetID(), JPH::EActivation::Activate);

		JPH::Body& body3 = *m_body_interface->CreateBody(JPH::BodyCreationSettings(sphere_shape,
																				   JPH::RVec3(10, 10, 0),
																				   JPH::Quat::sRotation(JPH::Vec3::sAxisX(), 0.25f * PI),
																				   JPH::EMotionType::Dynamic,
																				   Layers::MOVING));
		m_body_interface->AddBody(body3.GetID(), JPH::EActivation::Activate);
	}
}