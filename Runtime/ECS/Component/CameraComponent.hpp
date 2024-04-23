#pragma once

#include <Types.hpp>
#include <Component.hpp>
#include <Camera.hpp>

namespace Spore
{
	class CameraComponent : public Component
	{
	public:
		CameraComponent();
		virtual ~CameraComponent();
		virtual void InspectorPanel() override;
		virtual void Tick(float32 p_delta_time) override;
		void SetCamera(Camera* p_camera);
		Camera* GetCamera();

	protected:

	private:
		Camera* m_camera = nullptr;
	};
}