#include <GraphicRenderer.hpp>

namespace Spore
{
	GraphicRenderer::GraphicRenderer()
	{

	}

	GraphicRenderer::~GraphicRenderer()
	{

	}

	void GraphicRenderer::Init()
	{
		m_editor_camera = new Camera(vec3f(0.0f, 5.0f, 5.0f));
		m_render_pipeline = new RenderPipeline();
	}

	void GraphicRenderer::Terminate()
	{
		delete m_render_pipeline;
		delete m_editor_camera;
	}

	Camera* GraphicRenderer::GetCamera()
	{
		if (m_editor_camera != nullptr)
		{
			return m_editor_camera;
		}
		return nullptr;
	}

	RenderPipeline* GraphicRenderer::GetRenderPipeline()
	{
		if (m_render_pipeline != nullptr)
		{
			return m_render_pipeline;
		}
		return nullptr;
	}

	void GraphicRenderer::SetFlipVerticallyOnLoad(bool p_bool)
	{
		stbi_set_flip_vertically_on_load(p_bool);
	}
}