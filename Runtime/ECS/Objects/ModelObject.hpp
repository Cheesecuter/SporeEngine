#pragma once

#include <Types.hpp>
#include <Object.hpp>
#include <Model.hpp>
#include <ModelObserver.hpp>
#include <ShaderComponent.hpp>
#include <ModelComponent.hpp>
#include <PhysicsComponent.hpp>
#include <AudioComponent.hpp>

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
		Model* GetModel();
		void DeleteModel(Model* p_model);
		void DeleteModel(std::string p_identifier);
		void OnModelDeleted(Model* p_model) override;
		bool ModelMapperEmpty();
		void Render(Camera* p_camera, uint32 p_screen_width, uint32 p_screen_height) override;
		void SetModelType(ModelType p_model_type);
		ModelType GetModelType();

	protected:

	private:
		ModelType m_model_type = ModelType::CUBE;
	};
}
