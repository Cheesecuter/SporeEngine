#pragma once
#ifndef LAYERS_HPP
#define LAYERS_HPP

#include <JoltPhysics/Jolt/Jolt.h>
#include <JoltPhysics/Jolt/Physics/Collision/ObjectLayer.h>
#include <JoltPhysics/Jolt/Physics/Collision/BroadPhase/BroadPhaseLayer.h>

namespace Layers
{
	static constexpr JPH::ObjectLayer UNUSED1 = 0;
	static constexpr JPH::ObjectLayer UNUSED2 = 1;
	static constexpr JPH::ObjectLayer UNUSED3 = 2;
	static constexpr JPH::ObjectLayer UNUSED4 = 3;
	static constexpr JPH::ObjectLayer NON_MOVING = 4;
	static constexpr JPH::ObjectLayer MOVING = 5;
	static constexpr JPH::ObjectLayer DEBRIS = 6;
	static constexpr JPH::ObjectLayer SENSOR = 7;
	static constexpr JPH::ObjectLayer NUM_LAYERS = 8;
}

namespace BroadPhaseLayers
{
	static constexpr JPH::BroadPhaseLayer NON_MOVING(0);
	static constexpr JPH::BroadPhaseLayer MOVING(1);
	static constexpr JPH::BroadPhaseLayer DEBRIS(2);
	static constexpr JPH::BroadPhaseLayer SENSOR(3);
	static constexpr JPH::BroadPhaseLayer UNUSED(4);
	static constexpr Spore::uint32 NUM_LAYERS(5);
}

namespace Spore
{
	class ObjectLayerPairFilterImpl : public JPH::ObjectLayerPairFilter
	{
	public:
		virtual bool ShouldCollide(JPH::ObjectLayer p_object_1, JPH::ObjectLayer p_object_2) const override
		{
			switch (p_object_1)
			{
				case Layers::UNUSED1:
				case Layers::UNUSED2:
				case Layers::UNUSED3:
				case Layers::UNUSED4:
					return false;
				case Layers::NON_MOVING:
					return p_object_2 == Layers::MOVING || p_object_2 == Layers::DEBRIS;
				case Layers::MOVING:
					return p_object_2 == Layers::NON_MOVING || p_object_2 == Layers::MOVING || p_object_2 == Layers::SENSOR;
				case Layers::DEBRIS:
					return p_object_2 == Layers::NON_MOVING;
				case Layers::SENSOR:
					return p_object_2 == Layers::MOVING;
				default:
					JPH_ASSERT(false);
					return false;
			}
		}
	};

	class BPLayerInterfaceImpl final : public JPH::BroadPhaseLayerInterface
	{
	public:
		BPLayerInterfaceImpl()
		{
			m_object_to_broad_phase [Layers::UNUSED1] = BroadPhaseLayers::UNUSED;
			m_object_to_broad_phase [Layers::UNUSED2] = BroadPhaseLayers::UNUSED;
			m_object_to_broad_phase [Layers::UNUSED3] = BroadPhaseLayers::UNUSED;
			m_object_to_broad_phase [Layers::UNUSED4] = BroadPhaseLayers::UNUSED;
			m_object_to_broad_phase [Layers::NON_MOVING] = BroadPhaseLayers::NON_MOVING;
			m_object_to_broad_phase [Layers::MOVING] = BroadPhaseLayers::MOVING;
			m_object_to_broad_phase [Layers::DEBRIS] = BroadPhaseLayers::DEBRIS;
			m_object_to_broad_phase [Layers::SENSOR] = BroadPhaseLayers::SENSOR;
		}

		virtual uint32 GetNumBroadPhaseLayers() const override
		{
			return BroadPhaseLayers::NUM_LAYERS;
		}

		virtual JPH::BroadPhaseLayer GetBroadPhaseLayer(JPH::ObjectLayer p_layer) const override
		{
			JPH_ASSERT(p_layer < Layers::NUM_LAYERS);
			return m_object_to_broad_phase [p_layer];
		}

	#if defined(JPH_EXTERNAL_PROFILE) || defined(JPH_PROFILE_ENABLED)
		virtual const char* JPH::GetBroadPhaseLayerName(JPH::BroadPhaseLayer p_layer) const override
		{
			switch ((BroadPhaseLayer::Type) p_layer)
			{
				case (BroadPhaseLayer::Type) BroadPhaseLayers::NON_MOVING:	return "NON_MOVING";
				case (BroadPhaseLayer::Type) BroadPhaseLayers::MOVING:		return "MOVING";
				case (BroadPhaseLayer::Type) BroadPhaseLayers::DEBRIS:		return "DEBRIS";
				case (BroadPhaseLayer::Type) BroadPhaseLayers::SENSOR:		return "SENSOR";
				case (BroadPhaseLayer::Type) BroadPhaseLayers::UNUSED:		return "UNUSED";
				default:													JPH_ASSERT(false); return "INVALID";
			}
		}
	#endif

	private:
		JPH::BroadPhaseLayer m_object_to_broad_phase [Layers::NUM_LAYERS];
	};

	class ObjectVsBroadPhaseLayerFilterImpl : public JPH::ObjectVsBroadPhaseLayerFilter
	{
	public:
		virtual bool ShouldCollide(JPH::ObjectLayer p_layer_1, JPH::BroadPhaseLayer p_layer_2) const override
		{
			switch (p_layer_1)
			{
				case Layers::NON_MOVING:
					return p_layer_2 == BroadPhaseLayers::MOVING || p_layer_2 == BroadPhaseLayers::DEBRIS;
				case Layers::MOVING:
					return p_layer_2 == BroadPhaseLayers::NON_MOVING || p_layer_2 == BroadPhaseLayers::MOVING || p_layer_2 == BroadPhaseLayers::SENSOR;
				case Layers::DEBRIS:
					return p_layer_2 == BroadPhaseLayers::NON_MOVING;
				case Layers::SENSOR:
					return p_layer_2 == BroadPhaseLayers::MOVING;
				case Layers::UNUSED1:
				case Layers::UNUSED2:
				case Layers::UNUSED3:
					return false;
				default:
					JPH_ASSERT(false);
					return false;
			}
		}
	};
}

#endif
