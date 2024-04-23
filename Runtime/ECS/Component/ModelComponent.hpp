#pragma once

#include <Component.hpp>
#include <Model.hpp>
#include <ModelObserver.hpp>
#include <ModelType.hpp>

namespace Spore
{
	struct ModelTransformMatrixNode
	{
		mat4f m_projection;
		mat4f m_view;
		mat4f m_model;
	};

	class ModelComponent : public Component, public ModelObserver
	{
	public:
		ModelComponent();
		virtual ~ModelComponent();
		virtual void InspectorPanel() override;
		virtual void Tick(float32 p_delta_time) override;
		virtual void OnModelDeleted(Model* p_model) override;
		void SetModelType(ModelType p_model_type);
		ModelType GetModelType();
		void SetModelTransformMatrixNode(ModelTransformMatrixNode p_model_transform_matrix_node);
		void SetModelTransformMatrixNode(mat4f p_projection, mat4f p_view, mat4f p_model);
		ModelTransformMatrixNode GetModelTransformMatrixNode();
		void AddModel(Model* p_model);
		Model* GetModel();
		void DeleteModel(std::string p_identifier);

	protected:

	private:
		ModelType m_model_type = ModelType::CUBE;
		ModelTransformMatrixNode m_model_transform_matrix_node;
		std::map<std::string, Model*> m_model_mapper;
	};
}