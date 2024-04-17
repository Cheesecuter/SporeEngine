#include <GraphicRenderer.hpp>

namespace Spore
{
	GraphicRenderer::GraphicRenderer()
	{
		m_editor_camera = new Camera(vec3f(0.0f, 5.0f, 5.0f));
		m_render_pipeline = new RenderPipeline();
	}

	GraphicRenderer::~GraphicRenderer()
	{
		delete m_render_pipeline;
		delete m_editor_camera;
	}
}