#pragma once

#include <PhysicsTest.hpp>

namespace Spore
{
	class PTSimpleTest : public PhysicsTest
	{
	public:
		virtual ~PTSimpleTest() override;
		virtual void Init() override;
		bool IsActive() override;
		void Tick(uint32 step) override;

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
		std::vector<JPH::Body*> bodys;
	};
}