#include <Plane.hpp>

namespace Spore
{
	Plane::Plane(const std::string& identifier_p) : Object(identifier_p)
	{
		type = "plane";
		TransformComponent* transformComponent = new TransformComponent();
		ShaderComponent* shaderComponent = new ShaderComponent();
		modelMapper = std::map<std::string, Model*>();
		components [transformComponent->GetName()] = transformComponent;
		Shader* shadowMappingShader = AssetsManager::GetInstance().shaderMapper.find("ShadowMappingFragment.glsl")->second;
		shaderComponent->AddShader(shadowMappingShader);
		components [shaderComponent->GetName()] = shaderComponent;
		Init();
	}

	Plane::~Plane()
	{

	}

	void Plane::Init()
	{
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float32), (void*) 0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float32), (void*) (3 * sizeof(float32)));
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float32), (void*) (6 * sizeof(float32)));
		glBindVertexArray(0);
	}

	void Plane::Render(std::vector<Shader*> shaders_p, Texture* texture_p, mat4x4f model_p)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture_p->ID);
		ShaderComponent* shaderComponent = dynamic_cast<ShaderComponent*>(components.find("Shader")->second);
		for (uint32 i = 0; i < shaders_p.size(); i++)
		{
			shaderComponent->AddShader(shaders_p [i]);
		}
		for (std::pair<std::string, ShaderNode*> it_shader : shaderComponent->GetShaders())
		{
			if (it_shader.second->isLoading)
			{
				it_shader.second->shader->SetMat4("model", model_p);
			}
		}
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}
}