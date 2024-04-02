#include <Plane.hpp>

namespace Spore
{
	Plane::Plane(const std::string& p_identifier) : Object(p_identifier)
	{
		m_type = "plane";
		TransformComponent* transformComponent = new TransformComponent();
		ShaderComponent* shaderComponent = new ShaderComponent();
		m_model_mapper = std::map<std::string, Model*>();
		m_components [transformComponent->GetName()] = transformComponent;
		Shader* shadowMappingShader = AssetsManager::GetInstance().m_shader_mapper.find("ShadowMappingFragment.glsl")->second;
		shaderComponent->AddShader(shadowMappingShader);
		m_components [shaderComponent->GetName()] = shaderComponent;
		Init();
	}

	Plane::~Plane()
	{

	}

	void Plane::Init()
	{
		glGenVertexArrays(1, &m_VAO);
		glGenBuffers(1, &m_VBO);
		glBindVertexArray(m_VAO);
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertices), m_vertices, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float32), (void*) 0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float32), (void*) (3 * sizeof(float32)));
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float32), (void*) (6 * sizeof(float32)));
		glBindVertexArray(0);
	}

	void Plane::Render(std::vector<Shader*> p_shaders, Texture* p_texture, mat4x4f p_model)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, p_texture->m_ID);
		ShaderComponent* shaderComponent = dynamic_cast<ShaderComponent*>(m_components.find("Shader")->second);
		for (uint32 i = 0; i < p_shaders.size(); i++)
		{
			shaderComponent->AddShader(p_shaders [i]);
		}
		for (std::pair<std::string, ShaderNode*> it_shader : shaderComponent->GetShaders())
		{
			if (it_shader.second->m_is_loading)
			{
				it_shader.second->m_shader->SetMat4("model", p_model);
			}
		}
		glBindVertexArray(m_VAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}
}