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
		bool m_is_loading = true;
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

	public:

	protected:

	private:
		bool m_show_adding_uniforms_panel = false;
		bool m_uniform_name_exist = false;
		bool m_uniform_name_illegal = false;
		ShaderNode* m_selected_shadernode = nullptr;
		std::unordered_map<std::string, ShaderNode*> m_shaders;
		std::unordered_map<ShaderNode*, std::vector<UniformNode*>> m_uniforms;
		Texture* m_button_image_delete;

	public:
		/**
		 * @brief Display the inspector panel for the shader component.
		 *
		 * This function displays the inspector panel for the shader component.
		 * Allowing users to add, rename, delete shaders, and set uniforms.
		 */
		virtual void InspectorPanel() override;
		/**
		 * @brief Perform ticking operations for the shader component.
		 *
		 * @param p_delta_time The time elapsed since the last tick.
		 */
		virtual void Tick(float32 p_delta_time) override;
		/**
		 * @brief Add a shader to the shader component.
		 *
		 * @param p_shader Pointer to the shader to add.
		 */
		void AddShader(Shader* p_shader);
		/**
		 * @brief Remove a shader from the shader component.
		 *
		 * @param p_shader Pointer to the shader to remove.
		 */
		void RemoveShader(Shader* p_shader);
		/**
		 * @brief Get the shaders associated with the shader component.
		 *
		 * @return An unordered map containing the shaders.
		 */
		std::unordered_map<std::string, ShaderNode*> GetShaders() const;
		/**
		 * @brief Get the uniforms associated with the shader component.
		 *
		 * @return An unordered map containing the uniforms.
		 */
		std::unordered_map<ShaderNode*, std::vector<UniformNode*>> GetUniforms() const;

	protected:

	private:
		/**
		 * @brief Display the panel for adding uniforms to a shader node.
		 *
		 * @param p_shadernode Pointer to the shader node to which uniforms will be added.
		 */
		void AddingUniformsPanel(ShaderNode* p_shadernode);
	};
}
