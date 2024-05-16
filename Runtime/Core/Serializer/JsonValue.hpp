#pragma once

#include <Types.hpp>

namespace Spore
{
	enum class JsonType
	{
		Object,
		Array,
		String,
		Number,
		True,
		False,
		Null
	};

	class JsonValue
	{
	public:
		JsonValue();
		JsonValue(const std::string& p_value);
		JsonValue(float p_value);
		JsonValue(const std::vector<JsonValue>& p_value);
		JsonValue(const std::map<std::string, JsonValue>& p_value);
		JsonValue(const JsonValue& p_value);
		~JsonValue();
		JsonValue& operator=(const JsonValue& p_value);

	public:
		JsonType m_type;
		std::string m_string_value;
		float m_number_value;
		std::vector<JsonValue> m_array_value;
		std::map<std::string, JsonValue> m_object_value;

	protected:

	private:

	};
}