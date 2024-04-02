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
		PostProcess(std::string const& p_identifier, Shader* p_shader);
		~PostProcess();

		std::string m_identifier;
		Shader* m_shader;
		//std::vector<Shader*> shaders;
		
		void SetShader(Shader* p_shader);
		Shader* GetShader();
		void RenderToFBO(uint32 p_fbo);

	protected:

	private:

	};
}

#endif
