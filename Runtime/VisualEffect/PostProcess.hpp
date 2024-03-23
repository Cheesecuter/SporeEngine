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

	protected:

	private:

	};
}

#endif
