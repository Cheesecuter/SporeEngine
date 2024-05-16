#pragma once

#include <PhysicSystem.hpp>
#include <JsonParser.hpp>

namespace Spore
{
	class Serializer
	{
	public:
		Serializer();
		virtual ~Serializer();

	protected:

	private:
		PhysicSystem* m_physic_system = nullptr;
		JsonValue m_json_value;
		std::vector<Scene*> m_scenes;

	public:
		/**
		 * @brief Serialize the data to a JSON file.
		 *
		 * This function serializes the data to a JSON file specified by `p_path`.
		 * It constructs a JSON object representing the data and writes it to the file.
		 * Returns 0 if successful, otherwise returns a non-zero error code.
		 *
		 * @param p_path The path to the JSON file.
		 * @return 0 if successful, non-zero error code otherwise.
		 */
		int Serialize(const char* p_path);
		/**
		 * @brief Deserialize the data from a JSON file.
		 *
		 * This function deserializes the data from a JSON file specified by `p_path`.
		 * It reads the JSON data from the file, parses it, and reconstructs the objects and components accordingly.
		 * Returns 0 if successful, otherwise returns a non-zero error code.
		 *
		 * @param p_path The path to the JSON file.
		 * @return 0 if successful, non-zero error code otherwise.
		 */
		int Deserialize(const char* p_path);
		/**
		 * @brief Set the physics system for the serializer.
		 *
		 * This function sets the physics system for the serializer to interact with.
		 *
		 * @param p_physic_system Pointer to the physics system.
		 */
		void SetPhysicSystem(PhysicSystem* p_physic_system);
		/**
		 * @brief Set the scenes for the serializer.
		 *
		 * This function sets the scenes for the serializer to work with.
		 *
		 * @param p_scenes Vector of pointers to Scene objects.
		 */
		void SetScenes(std::vector<Scene*> p_scenes);
		/**
		 * @brief Get the scenes from the serializer.
		 *
		 * This function returns the vector of scenes currently stored in the serializer.
		 *
		 * @return Vector of pointers to Scene objects.
		 */
		std::vector<Scene*> GetScenes();

	protected:

	private:

	};
}