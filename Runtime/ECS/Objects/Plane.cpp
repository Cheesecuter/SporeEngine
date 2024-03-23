#include <Plane.hpp>

namespace Spore
{
	Plane::Plane(const std::string& identifier_p) : Object(identifier_p)
	{
		TransformComponent* transformComponent = new TransformComponent();
		modelMapper = std::map<std::string, Model*>();
		components [transformComponent->GetName()] = transformComponent;
		ShaderComponent* shaderComponent = new ShaderComponent();
		Shader* shader = AssetsManager::GetInstance().shaderMapper.find("ShadowMappingFragment.glsl")->second;
		modelShader = shader;
		shaderComponent->AddShader(modelShader);
		//Shader* lightingShader = AssetsManager::GetInstance().shaderMapper.find("LightingFragment.glsl")->second;
		//shaderComponent->AddShader(lightingShader);
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

	void Plane::Render(Shader* shader_p)
	{
		mat4x4f model = mat4x4f(1.0f);
		ShaderComponent* shaderComponent = dynamic_cast<ShaderComponent*>(components.find("Shader")->second);
		for (std::pair<std::string, ShaderNode*> it_shader : shaderComponent->GetShaders())
		{
			if (it_shader.second->isLoading)
			{
				it_shader.second->shader->SetMat4("model", model);
			}
		}
		//shader_p->SetMat4("model", model);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}
}