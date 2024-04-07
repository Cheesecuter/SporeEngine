#include <PTSimpleTest.hpp>
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

		JPH::BodyCreationSettings box1_settings(box_shape,
												JPH::RVec3(0, 10, 0),
												JPH::Quat::sIdentity(),
												JPH::EMotionType::Dynamic,
												Layers::MOVING);
		JPH::Body& body1 = *m_body_interface->CreateBody(box1_settings);
		m_body_interface->AddBody(body1.GetID(), JPH::EActivation::Activate);

		JPH::BodyCreationSettings box2_settings(box_shape,
												JPH::RVec3(5, 10, 0),
												JPH::Quat::sRotation(JPH::Vec3::sAxisX(), 0.25f * PI),
												JPH::EMotionType::Dynamic,
												Layers::MOVING);
		JPH::Body& body2 = *m_body_interface->CreateBody(box2_settings);
		m_body_interface->AddBody(body2.GetID(), JPH::EActivation::Activate);

		JPH::BodyCreationSettings sphere1_settings(sphere_shape,
												   JPH::RVec3(10, 10, 0),
												   JPH::Quat::sRotation(JPH::Vec3::sAxisX(), 0.25f * PI),
												   JPH::EMotionType::Dynamic,
												   Layers::MOVING);
		JPH::Body& body3 = *m_body_interface->CreateBody(sphere1_settings);
		m_body_interface->AddBody(body3.GetID(), JPH::EActivation::Activate);

		bodys.push_back(&body1);
		bodys.push_back(&body2);
		bodys.push_back(&body3);
	}

	bool PTSimpleTest::IsActive()
	{
		bool flag = false;
		for (int i = 0; i < bodys.size(); i++)
		{
			if (m_body_interface->IsActive(bodys [i]->GetID()))
			{
				flag = true;
			}
		}
		return flag;
	}

	void PTSimpleTest::Tick(uint32 step)
	{
		for (int i = 0; i < bodys.size(); i++)
		{

			JPH::RVec3 position = m_body_interface->GetCenterOfMassPosition(bodys[i]->GetID());
			JPH::Vec3 velocity = m_body_interface->GetLinearVelocity(bodys [i]->GetID());
			std::cout << "Step " << step << 
				": Position = (" << position.GetX() << ", " << position.GetY() << ", " << position.GetZ() << 
				"), Velocity = (" << velocity.GetX() << ", " << velocity.GetY() << ", " << velocity.GetZ() << ")" << std::endl;
		}
		std::cout << "\n";
	}
}