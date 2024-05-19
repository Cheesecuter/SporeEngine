#include <PostProcesser.hpp>
#include <ConsoleLogger.hpp>
#include <FrameBuffer.hpp>
#include <FrameBufferController.hpp>

namespace Spore
{
	PostProcesser::PostProcesser(uint32 p_scene_width, uint32 p_scene_height, PostProcess* p_post_process)
	{
		m_post_process = p_post_process;
		m_framebuffer = new FrameBuffer();
		m_framebuffer->m_identifier = "fb_post_process";
		FrameBufferController::GetInstance().AddFrameBuffer(m_framebuffer);
		glBindFramebuffer(GL_FRAMEBUFFER, m_framebuffer->m_framebuffer);

		glGenTextures(1, &m_texture);
		glBindTexture(GL_TEXTURE_2D, m_texture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, p_scene_width, p_scene_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_texture, 0);
		
		glGenRenderbuffers(1, &m_render_buffer);
		glBindRenderbuffer(GL_RENDERBUFFER, m_render_buffer);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, p_scene_width, p_scene_height);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_render_buffer);

		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		{
			ConsoleLogger::GetInstance().Logger()->error("PostProcesser::PostProcesser: Framebuffer is not complete");
		}
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		glGenVertexArrays(1, &m_quad_VAO);
		glGenBuffers(1, &m_quad_VBO);
		glBindVertexArray(m_quad_VAO);
		glBindBuffer(GL_ARRAY_BUFFER, m_quad_VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(m_quad_vertices), &m_quad_vertices, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*) 0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*) (2 * sizeof(float)));
	}

	PostProcesser::~PostProcesser()
	{

	}

	void PostProcesser::SetPostProcess(std::string p_identifier)
	{
		FrameBufferController::GetInstance().RemoveFrameBuffer(m_framebuffer->m_identifier);
		m_post_process = m_post_process_mapper[p_identifier];
		FrameBufferController::GetInstance().AddFrameBuffer(m_framebuffer);
	}

	void PostProcesser::AddPostProcess(PostProcess* p_post_process)
	{
		m_post_process_mapper [p_post_process->m_identifier] = p_post_process;
	}

	PostProcess* PostProcesser::GetPostProcess()
	{
		return m_post_process;
	}

	std::unordered_map<std::string, PostProcess*>* PostProcesser::GetPostProcesses()
	{
		return &m_post_process_mapper;
	}

	uint32 PostProcesser::GetFrameBufferTexture()
	{
		return m_texture;
	}

	uint32 PostProcesser::GetRenderBuffer()
	{
		return m_render_buffer;
	}

	void Render()
	{

	}

	void PostProcesser::RenderToFBO()
	{
		std::vector<std::string> framebuffers;
		framebuffers.push_back(m_framebuffer->m_identifier);
		//m_post_process->RenderToFBO(m_framebuffer->m_framebuffer);
		FrameBufferController::GetInstance().RenderToFBO(framebuffers, Render);
	}

	void PostProcesser::RenderFBO()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glDisable(GL_DEPTH_TEST);
		glClear(GL_COLOR_BUFFER_BIT);
		m_post_process->GetShader()->Use();
		glBindVertexArray(m_quad_VAO);
		glBindTexture(GL_TEXTURE_2D, m_texture);
		glBindFramebuffer(GL_FRAMEBUFFER, m_framebuffer->m_framebuffer);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	uint32 PostProcesser::GetQuadVAO()
	{
		return m_quad_VAO;
	}
}