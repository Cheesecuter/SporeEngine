#pragma once

#include <Types.hpp>
#include <Component.hpp>
#include <UUID.hpp>

namespace Spore
{
	class IDComponent : public Component
	{
	public:
		IDComponent();
		virtual ~IDComponent();

		virtual void InspectorPanel() override;
		void SetID(uint64 p_uuid);
		UUID GetID();

	protected:

	private:
		UUID m_UUID;
	};
}