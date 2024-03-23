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
}