#include <JsonValue.hpp>

namespace Spore
{
	JsonValue::JsonValue()
	{
		m_type = JsonType::Null;
		m_string_value = "";
		m_number_value = 0.0f;
	}

	JsonValue::JsonValue(const std::string& p_value)
	{
		m_type = JsonType::String;
		m_string_value = p_value;
		m_number_value = 0.0f;
	}

	JsonValue::JsonValue(float p_value)
	{
		m_type = JsonType::Number;
		m_string_value = "";
		m_number_value = p_value;
	}

	JsonValue::JsonValue(const std::vector<JsonValue>& p_value)
	{
		m_type = JsonType::Array;
		m_string_value = "";
		m_number_value = 0.0f;
		m_array_value = p_value;
	}

	JsonValue::JsonValue(const std::map<std::string, JsonValue>& p_value)
	{
		m_type = JsonType::Object;
		m_string_value = "";
		m_number_value = 0.0f;
		m_object_value = p_value;
	}

	JsonValue::JsonValue(const JsonValue& p_value)
	{
		m_type = p_value.m_type;
		m_string_value = p_value.m_string_value;
		m_number_value = p_value.m_number_value;
		m_array_value = p_value.m_array_value;
		m_object_value = p_value.m_object_value;
	}

	JsonValue::~JsonValue()
	{

	}

	JsonValue& JsonValue::operator=(const JsonValue& p_value)
	{
		if (this != &p_value)
		{
			m_type = p_value.m_type;
			m_string_value = p_value.m_string_value;
			m_number_value = p_value.m_number_value;
			m_array_value = p_value.m_array_value;
			m_object_value = p_value.m_object_value;
		}
		return *this;
	}
}