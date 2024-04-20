#pragma once

#include <Camera.hpp>
#include <RenderPipeline.hpp>

namespace Spore
{
	class GraphicRenderer
	{
	public:
		GraphicRenderer();
		~GraphicRenderer();
		void Init();
		void Terminate();
		Camera* GetCamera();
		RenderPipeline* GetRenderPipeline();
		void SetFlipVerticallyOnLoad(bool p_bool);

	private:
		Camera* m_editor_camera = nullptr;
		RenderPipeline* m_render_pipeline = nullptr;
	};
}