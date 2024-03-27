#include <PostProcess.hpp>

namespace Spore
{
	PostProcess::PostProcess(std::string const& identifier_p, Shader* shader_p) :
		identifier(identifier_p), shader(shader_p)
	{

	}

	PostProcess::~PostProcess()
	{

	}

	void PostProcess::SetShader(Shader* shader_p)
	{
		shader = shader_p;
		shader->Use();
		shader->SetInt("screenTexture", 0);
	}

	Shader* PostProcess::GetShader()
	{
		return shader;
	}

	void PostProcess::RenderToFBO(uint32 fbo_p)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, fbo_p);
		glEnable(GL_DEPTH_TEST);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
}