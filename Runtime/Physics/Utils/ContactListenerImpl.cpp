#include <ContactListenerImpl.hpp>

namespace Spore
{
	JPH::ValidateResult ContactListenerImpl::OnContactValidate(const JPH::Body& p_body_1, const JPH::Body& p_body_2,
															   JPH::RVec3Arg p_base_offset,
															   const JPH::CollideShapeResult& p_collision_result)
	{
		bool contract = p_body_1.GetMotionType() >= p_body_2.GetMotionType()
			|| (p_body_1.GetMotionType() == p_body_2.GetMotionType() && p_body_1.GetID() < p_body_2.GetID());
		if (!contract)
		{
			JPH_BREAKPOINT;
		}
		JPH::ValidateResult result;
		if (m_next != nullptr)
		{
			result = m_next->OnContactValidate(p_body_1, p_body_2, p_base_offset, p_collision_result);
		}
		else
		{
			result = JPH::ContactListener::OnContactValidate(p_body_1, p_body_2, p_base_offset, p_collision_result);
		}

		JPH::RVec3 contact_point = p_base_offset + p_collision_result.mContactPointOn1;

		JPH::Trace("Validate %u and %u result %d", p_body_1.GetID().GetIndex(), p_body_2.GetID().GetIndex(), (int) result);

		return result;
	}

	void ContactListenerImpl::OnContactAdded(const JPH::Body& p_body_1, const JPH::Body& p_body_2,
											 const JPH::ContactManifold& p_manifold, JPH::ContactSettings& p_settings)
	{
		if (!(p_body_1.GetID() < p_body_2.GetID()))
		{
			JPH_BREAKPOINT;
		}

		JPH::Trace("Contact added %u (%08x) and %u (%08x)",
				   p_body_1.GetID().GetIndex(), p_manifold.mSubShapeID1.GetValue(),
				   p_body_2.GetID().GetIndex(), p_manifold.mSubShapeID2.GetValue());

		{
			JPH::lock_guard clock(m_state_mutex);
			JPH::SubShapeIDPair key(p_body_1.GetID(), p_manifold.mSubShapeID1, p_body_2.GetID(), p_manifold.mSubShapeID2);
			if (m_state.find(key) != m_state.end())
			{
				JPH_BREAKPOINT;
			}
			m_state [key] = StatePair(p_manifold.mBaseOffset, p_manifold.mRelativeContactPointsOn1);
		}

		if (m_next != nullptr)
		{
			m_next->OnContactAdded(p_body_1, p_body_2, p_manifold, p_settings);
		}
	}

	void ContactListenerImpl::OnContactPersisted(const JPH::Body& p_body_1, const JPH::Body& p_body_2,
												 const JPH::ContactManifold& p_manifold, JPH::ContactSettings& p_settings)
	{
		if (!(p_body_1.GetID() < p_body_2.GetID()))
		{
			JPH_BREAKPOINT;
		}

		JPH::Trace("Contact persisted %u (%08x) and %u (%08x)",
				   p_body_1.GetID().GetIndex(), p_manifold.mSubShapeID1.GetValue(),
				   p_body_2.GetID().GetIndex(), p_manifold.mSubShapeID2.GetValue());

		{
			JPH::lock_guard clock(m_state_mutex);
			JPH::SubShapeIDPair key(p_body_1.GetID(), p_manifold.mSubShapeID1, p_body_2.GetID(), p_manifold.mSubShapeID2);
			StateMap::iterator it = m_state.find(key);
			if (it != m_state.end())
			{
				it->second = StatePair(p_manifold.mBaseOffset, p_manifold.mRelativeContactPointsOn1);
			}
			else
			{
				JPH_BREAKPOINT;
			}
		}

		if (m_next != nullptr)
		{
			m_next->OnContactPersisted(p_body_1, p_body_2, p_manifold, p_settings);
		}
	}

	void ContactListenerImpl::OnContactRemoved(const JPH::SubShapeIDPair& p_sub_shape_pair)
	{
		if (!(p_sub_shape_pair.GetBody1ID() < p_sub_shape_pair.GetBody2ID()))
		{
			JPH_BREAKPOINT;
		}

		JPH::Trace("Contact removed %u (%08x) and %u (%08x)",
				   p_sub_shape_pair.GetBody1ID().GetIndex(), p_sub_shape_pair.GetSubShapeID1().GetValue(),
				   p_sub_shape_pair.GetBody2ID().GetIndex(), p_sub_shape_pair.GetSubShapeID2().GetValue());

		{
			JPH::lock_guard clock(m_state_mutex);
			StateMap::iterator it = m_state.find(p_sub_shape_pair);
			if (it != m_state.end())
			{
				m_state.erase(it);
			}
			else
			{
				JPH_BREAKPOINT;
			}
		}

		if (m_next != nullptr)
		{
			m_next->OnContactRemoved(p_sub_shape_pair);
		}
	}

	void ContactListenerImpl::SaveState(JPH::StateRecorder& p_stream) const
	{

	}

	void ContactListenerImpl::RestoreState(JPH::StateRecorder& p_stream)
	{

	}

	void ContactListenerImpl::DrawState()
	{

	}

	void ContactListenerImpl::SetNextListener(JPH::ContactListener* p_listener)
	{
		m_next = p_listener;
	}
}