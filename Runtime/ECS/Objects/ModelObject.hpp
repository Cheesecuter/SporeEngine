#pragma once

#include <Types.hpp>
#include <Object.hpp>
#include <Model.hpp>
#include <PhysicsComponent.hpp>

namespace Spore
{
	class ModelObject : public Object
	{
	public:
		ModelObject(const std::string& p_identifier);
		~ModelObject();

		std::map<std::string, Model*> m_model_mapper;
		uint32 m_VAO, m_VBO, m_EBO;
		bool m_flag_run = false;
		bool m_flag_stop = true;

		void AddModel(Model* p_model);
		void DeleteModel(Model* p_model);
		void DeleteModel(std::string p_identifier);
		void OnModelDeleted(Model* p_model) override;
		void Render(std::vector<Shader*> p_shaders, Camera* p_camera,
					uint32 p_screen_width, uint32 p_screen_height,
					mat4f p_projection, mat4f p_view, mat4f p_model) override;

	protected:

	private:

	};
}
