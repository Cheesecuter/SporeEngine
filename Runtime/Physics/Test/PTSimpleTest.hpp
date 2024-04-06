#pragma once

#include <PhysicsTest.hpp>
#include <JoltPhysics/Jolt/Physics/Body/BodyActivationListener.h>

namespace Spore
{
	class PTSimpleTest : public PhysicsTest
	{
	public:
		virtual ~PTSimpleTest() override;
		virtual void Init() override;

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