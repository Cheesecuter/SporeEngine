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

	private:
		Camera* m_editor_camera = nullptr;
		RenderPipeline* m_render_pipeline = nullptr;
	};
}