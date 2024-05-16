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

	public:
		std::map<std::string, Model*> m_model_mapper;
		uint32 m_VAO, m_VBO, m_EBO;
		bool m_flag_run = false;
		bool m_flag_stop = true;

	protected:

	private:
		ModelType m_model_type = ModelType::CUBE;

	public:
		/**
		 * @brief Add a model to the model object.
		 *
		 * This function adds a model to the model object by adding it to the model component associated with the object.
		 *
		 * @param p_model Pointer to the model to be added.
		 */
		void AddModel(Model* p_model);
		/**
		 * @brief Get the model associated with the model object.
		 *
		 * This function retrieves the model associated with the model object from its model component.
		 *
		 * @return Pointer to the model associated with the model object.
		 */
		Model* GetModel();
		/**
		 * @brief Delete a model from the model object.
		 *
		 * This function deletes a model from the model object by removing it from the model component associated with the object.
		 *
		 * @param p_model Pointer to the model to be deleted.
		 */
		void DeleteModel(Model* p_model);
		/**
		 * @brief Delete a model from the model object using its identifier.
		 *
		 * This function deletes a model from the model object by removing it from the model component associated with the object,
		 * using the provided model identifier.
		 *
		 * @param p_identifier The identifier of the model to be deleted.
		 */
		void DeleteModel(std::string p_identifier);
		void OnModelDeleted(Model* p_model) override;
		/**
		 * @brief Check if the model mapper is empty.
		 *
		 * This function checks if the model mapper associated with the model object is empty by
		 * verifying if the model component's model pointer is nullptr.
		 *
		 * @return True if the model mapper is empty, false otherwise.
		 */
		bool ModelMapperEmpty();
		/**
		 * @brief Set the model type for the model object.
		 *
		 * This function sets the model type for the model object by forwarding the call to its associated model component.
		 *
		 * @param p_model_type The model type to set for the model object.
		 */
		void SetModelType(ModelType p_model_type);
		/**
		 * @brief Get the model type of the model object.
		 *
		 * This function retrieves the model type of the model object from its associated model component.
		 *
		 * @return The model type of the model object.
		 */
		ModelType GetModelType();
		/**
		 * @brief Render the model object.
		 *
		 * This function renders the model object using the provided camera and screen dimensions.
		 *
		 * @param p_camera Pointer to the camera used for rendering.
		 * @param p_screen_width Width of the screen in pixels.
		 * @param p_screen_height Height of the screen in pixels.
		 */
		void Render(Camera* p_camera, uint32 p_screen_width, uint32 p_screen_height) override;

	protected:

	private:

	};
}
