#pragma once
#ifndef POST_PROCESS_HPP
#define POST_PROCESS_HPP

#include <Types.hpp>
#include <Shader.hpp>

namespace Spore
{
	class PostProcess
	{
	public:
		PostProcess(std::string& identifier_p, Shader* shader_p);
		~PostProcess();

		std::string identifier;
		Shader* shader;
		//std::vector<Shader*> shaders;
		
		void SetShader(Shader* shader_p);
		Shader* GetShader();
		void Render(uint32 fbo_p, uint32 texture_p, uint32 quadVAO_p, mat4f projection_p, mat4f view_p, mat4f model_p);

	protected:

	private:

	};
}

#endif
