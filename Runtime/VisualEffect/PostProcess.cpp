#include <PostProcess.hpp>

namespace Spore
{
	PostProcess::PostProcess(std::string& identifier_p, Shader* shader_p) :
		identifier(identifier_p), shader(shader_p)
	{

	}

	PostProcess::~PostProcess()
	{

	}

	void PostProcess::SetShader(Shader* shader_p)
	{
		shader = shader_p;
	}

	Shader* PostProcess::GetShader()
	{
		return shader;
	}

	void PostProcess::Render(uint32 fbo_p)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, fbo_p);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		shader->Use();
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glClear(GL_COLOR_BUFFER_BIT);
		shader->Use();
	}
}