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

	void PostProcess::Render(uint32 fbo_p, uint32 texture_p, uint32 quadVAO_p, mat4f projection_p, mat4f view_p, mat4f model_p)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, fbo_p);
		glEnable(GL_DEPTH_TEST);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		shader->Use();
		shader->SetMat4("view", view_p);
		shader->SetMat4("projection", projection_p);

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glClear(GL_COLOR_BUFFER_BIT);

		shader->Use();
		glBindVertexArray(quadVAO_p);
		glBindTexture(GL_TEXTURE_2D, texture_p);
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}
}