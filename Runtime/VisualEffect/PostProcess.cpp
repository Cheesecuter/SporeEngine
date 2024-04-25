#include <PostProcess.hpp>

namespace Spore
{
	PostProcess::PostProcess(std::string const& p_identifier, Shader* p_shader) :
		m_identifier(p_identifier), m_shader(p_shader)
	{

	}

	PostProcess::~PostProcess()
	{

	}

	void PostProcess::SetShader(Shader* p_shader)
	{
		m_shader = p_shader;
		m_shader->Use();
		m_shader->SetInt("screenTexture", 0);
		m_shader->SetFloat("iTime", glfwGetTime());
		m_shader->SetVec3("iResolution", 1024, 1024, 1024);
	}

	Shader* PostProcess::GetShader()
	{
		return m_shader;
	}

	void PostProcess::RenderToFBO(uint32 p_fbo)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, p_fbo);
		glEnable(GL_DEPTH_TEST);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
}