#pragma once

#include <Component.hpp>

namespace Spore
{
	class CharacterControllerComponent : public Component
	{
	public:
		CharacterControllerComponent();
		virtual ~CharacterControllerComponent();
		virtual void InspectorPanel() override;
		virtual void Tick(float32 p_delta_time) override;


	protected:

	private:

	};
}