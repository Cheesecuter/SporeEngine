#pragma once

#include <Types.hpp>
#include <Component.hpp>
#include <Shader.hpp>

namespace Spore
{
	struct ShaderNode
	{
		bool m_is_loading = true;
		Shader* m_shader;
	};

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
		std::unordered_map<std::string, ShaderNode*> m_shaders;
	};
}
