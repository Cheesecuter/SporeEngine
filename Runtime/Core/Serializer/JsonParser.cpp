#include <JsonParser.hpp>

namespace Spore
{
	JsonParser::JsonParser()
	{

	}

	JsonParser::~JsonParser()
	{

	}

	JsonValue JsonParser::parse(const std::string& jsonStr)
	{
		index = 0;
		return parseValue(jsonStr);
	}

	JsonValue JsonParser::parseValue(const std::string& jsonStr)
	{
		skipWhilespace(jsonStr);
		char ch = jsonStr [index];
		if (ch == '{')
		{
			return parseObject(jsonStr);
		}
		else if (ch == '[')
		{
			return parseArray(jsonStr);
		}
		else if (ch == '"')
		{
			return parseString(jsonStr);
		}
		else if (isdigit(ch) || ch == '-')
		{
			return parseNumber(jsonStr);
		}
		else if (jsonStr.substr(index, 4) == "true")
		{
			index += 4;
		}
		else if (jsonStr.substr(index, 5) == "false")
		{
			index += 5;
		}
		else if (jsonStr.substr(index, 4) == "null")
		{
			index += 4;
			return{ JsonValue() };
		}
		throw std::runtime_error("Invalid JSON");
	}

	JsonValue JsonParser::parseObject(const std::string& jsonStr)
	{
		JsonValue obj;
		index++;
		while (jsonStr [index] != '}')
		{
			skipWhilespace(jsonStr);
			std::string key = parseString(jsonStr).m_string_value;
			skipWhilespace(jsonStr);
			if (jsonStr [index] != ':')
			{
				throw std::runtime_error("Expected colon in object");
			}
			index++;
			JsonValue value = parseValue(jsonStr);
			obj.m_object_value [key] = value;
			skipWhilespace(jsonStr);
			if (jsonStr [index] == ',')
			{
				index++;
			}
			else if (jsonStr [index] != '}')
			{
				throw std::runtime_error("Expedted comma or closing brace in object");
			}
		}
		index++;
		obj.m_type = JsonType::Object;
		return obj;
	}

	JsonValue JsonParser::parseArray(const std::string& jsonStr)
	{
		JsonValue arr;
		index++;
		while (jsonStr [index] != ']')
		{
			skipWhilespace(jsonStr);
			arr.m_array_value.push_back(parseValue(jsonStr));
			skipWhilespace(jsonStr);
			if (jsonStr [index] == ',')
			{
				index++;
			}
			else if (jsonStr [index] != ']')
			{
				throw std::runtime_error("Expected comma or closing bracked in array");
			}
		}
		index++;
		arr.m_type = JsonType::Array;
		return arr;
	}

	JsonValue JsonParser::parseString(const std::string& jsonStr)
	{
		JsonValue str;
		index++;
		int start = index;
		while (jsonStr [index] != '"')
		{
			if (jsonStr [index] == '\\')
			{
				index += 2;
			}
			else
			{
				index++;
			}
		}
		str.m_string_value = jsonStr.substr(start, index - start);
		index++;
		str.m_type = JsonType::String;
		return str;
	}

	JsonValue JsonParser::parseNumber(const std::string& jsonStr)
	{
		JsonValue num;
		int start = index;
		while (isdigit(jsonStr [index]) || jsonStr [index] == '.' || jsonStr [index] == '-')
		{
			index++;
		}
		std::string numStr = jsonStr.substr(start, index - start);
		num.m_number_value = (float32) stod(numStr);
		num.m_type = JsonType::Number;
		return num;
	}

	void JsonParser::skipWhilespace(const std::string& jsonStr)
	{
		while (isspace(jsonStr [index]))
		{
			index++;
		}
	}

	std::string JsonParser::toJsonString(JsonValue p_value) const
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
					jsonStr += "\"" + pair.first + "\":" + toJsonString(pair.second);
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
					jsonStr += toJsonString(val);
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
}
