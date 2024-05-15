#pragma once

#include <Types.hpp>
#include <Component.hpp>
#include <Shader.hpp>
#include <ShaderUniformType.hpp>

namespace Spore
{
	struct ShaderNode
	{
		bool m_is_loading = true;
		Shader* m_shader;
	};

	struct UniformNode
	{
		ShaderUniformType m_type = ShaderUniformType::NONE;
		std::string m_name = "unknown uniform";
		bool m_bool = false;
		int32 m_int = 0;
		float32 m_float = 0.0f;
		vec2f m_vec2 = vec2f(0.0f);
		vec3f m_vec3 = vec3f(0.0f);
		vec4f m_vec4 = vec4f(0.0f);
		mat2f m_mat2 = mat2f(0.0f);
		mat3f m_mat3 = mat3f(0.0f);
		mat4f m_mat4 = mat4f(0.0f);
	};

	class Texture;

	class ShaderComponent : public Component
	{
	public:
		ShaderComponent();
		virtual ~ShaderComponent();
		virtual void InspectorPanel() override;
		virtual void Tick(float32 p_delta_time) override;
		void AddShader(Shader* p_shader);
		void RemoveShader(Shader* p_shader);
		std::unordered_map<std::string, ShaderNode*> GetShaders() const;

	protected:

	private:
		bool m_show_adding_uniforms_panel = false;
		bool m_uniform_name_exist = false;
		bool m_uniform_name_illegal = false;
		std::string m_selected_shader_identifier = "";
		std::unordered_map<std::string, ShaderNode*> m_shaders;
		std::unordered_map<std::string, std::vector<UniformNode*>> m_uniforms;
		Texture* m_button_image_delete;

		void AddingUniformsPanel(std::string p_shader_identifier);
	};
}
