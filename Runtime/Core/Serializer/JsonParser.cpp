#include <JsonParser.hpp>
#include <ConsoleLogger.hpp>

namespace Spore
{
	JsonParser::JsonParser()
	{

	}

	JsonParser::~JsonParser()
	{

	}

	JsonValue JsonParser::Parse(const std::string& p_json_str)
	{
		index = 0;
		return ParseValue(p_json_str);
	}

	std::string JsonParser::ToJsonString(JsonValue p_value) const
	{
		switch (p_value.m_type)
		{
			case JsonType::Object:
			{
				std::string jsonStr = "{";
				bool isFirst = true;
				for (const auto& pair : p_value.m_object_value)
				{
					if (!isFirst)
					{
						jsonStr += ",";
					}
					jsonStr += "\"" + pair.first + "\":" + ToJsonString(pair.second);
					isFirst = false;
				}
				jsonStr += "}";
				return jsonStr;
			}
			case JsonType::Array:
			{
				std::string jsonStr = "[";
				bool isFirst = true;
				for (const auto& val : p_value.m_array_value)
				{
					if (!isFirst)
					{
						jsonStr += ",";
					}
					jsonStr += ToJsonString(val);
					isFirst = false;
				}
				jsonStr += "]";
				return jsonStr;
			}
			case JsonType::String:
				return "\"" + p_value.m_string_value + "\"";
			case JsonType::Number:
				return std::to_string(p_value.m_number_value);
			case JsonType::True:
				return "true";
			case JsonType::False:
				return "false";
			case JsonType::Null:
				return "null";
			default:
				return "";
				break;
		}
	}

	JsonValue JsonParser::ParseValue(const std::string& p_json_str)
	{
		SkipWhilespace(p_json_str);
		char ch = p_json_str [index];
		try
		{
			if (ch == '{')
			{
				return ParseObject(p_json_str);
			}
			else if (ch == '[')
			{
				return ParseArray(p_json_str);
			}
			else if (ch == '"')
			{
				return ParseString(p_json_str);
			}
			else if (isdigit(ch) || ch == '-')
			{
				return ParseNumber(p_json_str);
			}
			else if (p_json_str.substr(index, 4) == "true")
			{
				index += 4;
			}
			else if (p_json_str.substr(index, 5) == "false")
			{
				index += 5;
			}
			else if (p_json_str.substr(index, 4) == "null")
			{
				index += 4;
				return{ JsonValue() };
			}
		}
		catch (std::runtime_error e)
		{
			ConsoleLogger::GetInstance().Logger()->error("JsonParser::ParseValue: Invalid JSON");
			throw std::runtime_error("Invalid JSON");
			return{ JsonValue() };
		}

		return{ JsonValue() };
	}

	JsonValue JsonParser::ParseObject(const std::string& p_json_str)
	{
		JsonValue obj;
		index++;
		while (p_json_str [index] != '}')
		{
			SkipWhilespace(p_json_str);
			std::string key = ParseString(p_json_str).m_string_value;
			SkipWhilespace(p_json_str);
			if (p_json_str [index] != ':')
			{
				ConsoleLogger::GetInstance().Logger()->error("JsonParser::ParseObject: Expected colon in object");
				throw std::runtime_error("Expected colon in object");
			}
			index++;
			JsonValue value = ParseValue(p_json_str);
			obj.m_object_value [key] = value;
			SkipWhilespace(p_json_str);
			if (p_json_str [index] == ',')
			{
				index++;
			}
			else if (p_json_str [index] != '}')
			{
				ConsoleLogger::GetInstance().Logger()->error("JsonParser::ParseObject: Expedted comma or closing brace in object");
				throw std::runtime_error("Expedted comma or closing brace in object");
			}
		}
		index++;
		obj.m_type = JsonType::Object;
		return obj;
	}

	JsonValue JsonParser::ParseArray(const std::string& p_json_str)
	{
		JsonValue arr;
		index++;
		while (p_json_str [index] != ']')
		{
			SkipWhilespace(p_json_str);
			arr.m_array_value.push_back(ParseValue(p_json_str));
			SkipWhilespace(p_json_str);
			if (p_json_str [index] == ',')
			{
				index++;
			}
			else if (p_json_str [index] != ']')
			{
				ConsoleLogger::GetInstance().Logger()->error("JsonParser::ParseObject: Expected comma or closing bracked in array");
				throw std::runtime_error("Expected comma or closing bracked in array");
			}
		}
		index++;
		arr.m_type = JsonType::Array;
		return arr;
	}

	JsonValue JsonParser::ParseString(const std::string& p_json_str)
	{
		JsonValue str;
		index++;
		int start = index;
		while (p_json_str [index] != '"')
		{
			if (p_json_str [index] == '\\')
			{
				index += 2;
			}
			else
			{
				index++;
			}
		}
		str.m_string_value = p_json_str.substr(start, index - start);
		index++;
		str.m_type = JsonType::String;
		return str;
	}

	JsonValue JsonParser::ParseNumber(const std::string& p_json_str)
	{
		JsonValue num;
		int start = index;
		while (isdigit(p_json_str [index]) || p_json_str [index] == '.' || p_json_str [index] == '-')
		{
			index++;
		}
		std::string numStr = p_json_str.substr(start, index - start);
		num.m_number_value = (float32) stod(numStr);
		num.m_type = JsonType::Number;
		return num;
	}

	void JsonParser::SkipWhilespace(const std::string& p_json_str)
	{
		while (isspace(p_json_str [index]))
		{
			index++;
		}
	}
}
