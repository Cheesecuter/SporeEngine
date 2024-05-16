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

	public:

	protected:

	private:
		ModelType m_model_type = ModelType::CUBE;
		ModelTransformMatrixNode m_model_transform_matrix_node;
		std::map<std::string, Model*> m_model_mapper;

	public:
		/**
		 * @brief Render the inspector panel for the model component.
		 *
		 * This function renders the inspector panel for the model component using ImGui.
		 * It allows users to add models to the component.
		 */
		virtual void InspectorPanel() override;
		/**
		 * @brief Update the model component's state.
		 *
		 * This function updates the model component's state, including applying transformations and rendering the model.
		 *
		 * @param p_delta_time The time elapsed since the last update.
		 */
		virtual void Tick(float32 p_delta_time) override;
		/**
		 * @brief Handle the event when a model is deleted.
		 *
		 * This function removes the specified model from the model mapper.
		 *
		 * @param p_model Pointer to the model that is deleted.
		 */
		virtual void OnModelDeleted(Model* p_model) override;
		/**
		 * @brief Set the model type for the model component.
		 *
		 * @param p_model_type The model type to set.
		 */
		void SetModelType(ModelType p_model_type);
		/**
		 * @brief Get the model type of the model component.
		 *
		 * @return The model type of the model component.
		 */
		ModelType GetModelType();
		/**
		 * @brief Set the model transform matrix node for the model component.
		 *
		 * @param p_model_transform_matrix_node The model transform matrix node to set.
		 */
		void SetModelTransformMatrixNode(ModelTransformMatrixNode p_model_transform_matrix_node);
		/**
		 * @brief Set the model transform matrix node for the model component.
		 *
		 * @param p_projection The projection matrix.
		 * @param p_view The view matrix.
		 * @param p_model The model matrix.
		 */
		void SetModelTransformMatrixNode(mat4f p_projection, mat4f p_view, mat4f p_model);
		/**
		 * @brief Get the model transform matrix node of the model component.
		 *
		 * @return The model transform matrix node of the model component.
		 */
		ModelTransformMatrixNode GetModelTransformMatrixNode();
		/**
		 * @brief Add a model to the model component.
		 *
		 * This function adds the specified model to the model mapper and sets this component as an observer of the model.
		 *
		 * @param p_model Pointer to the model to add.
		 */
		void AddModel(Model* p_model);
		/**
		 * @brief Get the model associated with the model component.
		 *
		 * @return Pointer to the model associated with the model component.
		 *         Returns nullptr if no model is associated.
		 */
		Model* GetModel();
		/**
		 * @brief Delete a model from the model component.
		 *
		 * This function removes the model with the specified identifier from the model mapper
		 * and removes this component as an observer of the model.
		 *
		 * @param p_identifier The identifier of the model to delete.
		 */
		void DeleteModel(std::string p_identifier);

	protected:

	private:

	};
}