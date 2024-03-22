#include <ShaderComponent.hpp>

namespace Spore
{
	ShaderComponent::ShaderComponent()
	{
		name = "Shader";
	}

	void ShaderComponent::AddShader(Shader* shader_p)
	{
		if (shaders.find(shader_p->identifier) != shaders.end())
		{
			shaders [shader_p->identifier]->shader = shader_p;
		}
		else
		{
			ShaderNode* shaderNode = new ShaderNode();
			shaderNode->shader = shader_p;
			shaders [shader_p->identifier] = shaderNode;
		}
		//shaders [shader_p->identifier] = shader_p;
	}

	void ShaderComponent::RemoveShader(Shader* shader_p)
	{
		shaders.erase(shader_p->identifier);
	}

	std::unordered_map<std::string, ShaderNode*> ShaderComponent::GetShaders() const
	{
		return shaders;
	}
}