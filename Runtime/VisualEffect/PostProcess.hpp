#pragma once
#ifndef POST_PROCESS_HPP
#define POST_PROCESS_HPP

#include <Types.hpp>
#include <Shader.hpp>
#include <Camera.hpp>

namespace Spore
{
	class PostProcess
	{
	public:
		PostProcess(std::string const& identifier_p, Shader* shader_p);
		~PostProcess();

		std::string identifier;
		Shader* shader;
		//std::vector<Shader*> shaders;
		
		void SetShader(Shader* shader_p);
		Shader* GetShader();
		void RenderToFBO(uint32 fbo_p);

	protected:

	private:

	};
}

#endif
