#pragma once

#include <Types.hpp>
#include <JsonValue.hpp>
#include <Scene.hpp>
#include <Light.hpp>
#include <ModelObject.hpp>
#include <Model.hpp>
#include <Shader.hpp>
#include <Scene.hpp>
#include <TransformComponent.hpp>
#include <ShaderComponent.hpp>
#include <PhysicsComponent.hpp>
#include <AudioComponent.hpp>
#include <PhysicSystem.hpp>

namespace Spore
{
	class JsonParser
	{
	public:
		JsonParser();
		virtual ~JsonParser();

	protected:

	private:
		int index;
	
	public:
		/**
		 * @brief Parse a JSON string into a JsonValue.
		 *
		 * This function initializes the parser state and parses the entire JSON string
		 * `p_json_str` into a JsonValue object. It resets the index and calls `ParseValue`
		 * to perform the actual parsing.
		 *
		 * @param p_json_str The JSON string to parse.
		 * @return The parsed JsonValue object.
		 * @throw std::runtime_error If the JSON string is invalid.
		 */
		JsonValue Parse(const std::string& p_json_str);
		/**
		 * @brief Convert a JsonValue to its JSON string representation.
		 *
		 * This function takes a JsonValue `p_value` and converts it to a JSON string.
		 * It handles different JSON types including objects, arrays, strings, numbers,
		 * booleans, and null.
		 *
		 * @param p_value The JsonValue to convert.
		 * @return The JSON string representation of the JsonValue.
		 */
		std::string ToJsonString(JsonValue p_value) const;

	protected:

	private:
		/**
		 * @brief Parse a JSON string into a JsonValue.
		 *
		 * This function takes a JSON string `p_json_str` and parses it into a JsonValue object.
		 * It determines the type of JSON value (object, array, string, number, boolean, or null)
		 * and calls the appropriate parsing function.
		 *
		 * @param p_json_str The JSON string to parse.
		 * @return The parsed JsonValue object.
		 * @throw std::runtime_error If the JSON string is invalid.
		 */
		JsonValue ParseValue(const std::string& p_json_str);
		/**
		 * @brief Parse a JSON object from a JSON string.
		 *
		 * This function takes a JSON string `p_json_str` and parses it into a JsonValue object
		 * representing a JSON object. It reads key-value pairs, handling nested objects and arrays
		 * as needed, and returns the resulting JsonValue.
		 *
		 * @param p_json_str The JSON string to parse.
		 * @return The parsed JsonValue object representing the JSON object.
		 * @throw std::runtime_error If the JSON object is malformed.
		 */
		JsonValue ParseObject(const std::string& p_json_str);
		/**
		 * @brief Parse a JSON array from a JSON string.
		 *
		 * This function takes a JSON string `p_json_str` and parses it into a JsonValue object
		 * representing a JSON array. It reads values within the array, handling nested objects and arrays
		 * as needed, and returns the resulting JsonValue.
		 *
		 * @param p_json_str The JSON string to parse.
		 * @return The parsed JsonValue object representing the JSON array.
		 * @throw std::runtime_error If the JSON array is malformed.
		 */
		JsonValue ParseArray(const std::string& p_json_str);
		/**
		 * @brief Parse a JSON string from a JSON string.
		 *
		 * This function takes a JSON string `p_json_str` and parses it into a JsonValue object
		 * representing a JSON string. It handles escape sequences and reads until the closing
		 * double-quote character.
		 *
		 * @param p_json_str The JSON string to parse.
		 * @return The parsed JsonValue object representing the JSON string.
		 * @throw std::runtime_error If the JSON string is malformed.
		 */
		JsonValue ParseString(const std::string& p_json_str);
		/**
		 * @brief Parse a JSON number from a JSON string.
		 *
		 * This function takes a JSON string `p_json_str` and parses it into a JsonValue object
		 * representing a JSON number. It reads digits, decimal points, and negative signs to
		 * construct the number.
		 *
		 * @param p_json_str The JSON string to parse.
		 * @return The parsed JsonValue object representing the JSON number.
		 * @throw std::runtime_error If the JSON number is malformed.
		 */
		JsonValue ParseNumber(const std::string& p_json_str);
		/**
		 * @brief Skip whitespace characters in a JSON string.
		 *
		 * This function advances the `index` past any whitespace characters
		 * in the JSON string `p_json_str`. It stops at the first non-whitespace
		 * character.
		 *
		 * @param p_json_str The JSON string to process.
		 */
		void SkipWhilespace(const std::string& p_json_str);
	};
}
