#pragma once

#include <Types.hpp>
#include <PostProcess.hpp>

namespace Spore
{
	class FrameBuffer;
	class PostProcesser
	{
	public:
		PostProcesser(uint32 p_scene_width, uint32 p_scene_height, PostProcess* p_post_process);
		~PostProcesser();

		void SetPostProcess(std::string p_identifier);
		void AddPostProcess(PostProcess* p_post_process);
		PostProcess* GetPostProcess();
		std::unordered_map<std::string, PostProcess*>* GetPostProcesses();
		uint32 GetFrameBufferTexture();
		uint32 GetRenderBuffer();
		void RenderToFBO();
		void RenderFBO();
		uint32 GetQuadVAO();

	protected:

	private:
		uint32 m_quad_VAO, m_quad_VBO;
		FrameBuffer* m_framebuffer;
		uint32 m_texture;
		uint32 m_render_buffer;
		PostProcess* m_post_process;
		std::unordered_map<std::string, PostProcess*> m_post_process_mapper;
		float m_quad_vertices [24] = { 
		// vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
		// positions   // texCoords
		-1.0f,  1.0f,  0.0f, 1.0f,
		-1.0f, -1.0f,  0.0f, 0.0f,
		 1.0f, -1.0f,  1.0f, 0.0f,

		-1.0f,  1.0f,  0.0f, 1.0f,
		 1.0f, -1.0f,  1.0f, 0.0f,
		 1.0f,  1.0f,  1.0f, 1.0f
		};
	};
}
