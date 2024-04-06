#pragma once

#include <JoltPhysics/Jolt/Jolt.h>
#include <JoltPhysics/Jolt/Physics/Body/Body.h>
#include <JoltPhysics/Jolt/Physics/Collision/CollideShape.h>
#include <JoltPhysics/Jolt/Physics/Collision/ContactListener.h>
#include <JoltPhysics/Jolt/Physics/StateRecorder.h>
#include <JoltPhysics/Jolt/Core/Mutex.h>
#include <JoltPhysics/Jolt/Core/UnorderedMap.h>
#include <JoltPhysics/Jolt/Core/QuickSort.h>

namespace Spore
{
	class ContactListenerImpl : public JPH::ContactListener
	{
	public:
		virtual JPH::ValidateResult OnContactValidate(const JPH::Body& p_body_1, const JPH::Body& p_body_2,
													  JPH::RVec3Arg p_base_offset,
													  const JPH::CollideShapeResult& p_collision_result) override;
		virtual void OnContactAdded(const JPH::Body& p_body_1, const JPH::Body& p_body_2,
									const JPH::ContactManifold & p_manifold, JPH::ContactSettings & p_settings) override;
		virtual void OnContactPersisted(const JPH::Body& p_body_1, const JPH::Body& p_body_2,
										const JPH::ContactManifold& p_manifold, JPH::ContactSettings& p_settings) override;
		virtual void OnContactRemoved(const JPH::SubShapeIDPair& p_sub_shape_pair) override;
		void SaveState(JPH::StateRecorder& p_stream) const;
		void RestoreState(JPH::StateRecorder& p_stream);
		void DrawState();
		void SetNextListener(JPH::ContactListener* p_listener);

	private:
		using StatePair = std::pair<JPH::RVec3, JPH::ContactPoints>;
		using StateMap = JPH::UnorderedMap<JPH::SubShapeIDPair, StatePair>;
		JPH::Mutex m_state_mutex;
		StateMap m_state;
		JPH::ContactListener* m_next = nullptr;
	};
}
