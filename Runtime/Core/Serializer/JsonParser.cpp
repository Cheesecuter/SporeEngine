//#include <iostream>
//#include <fstream>
//#include <string>
//#include <map>
//#include <vector>
//
//#include <Scene.hpp>
//#include <Light.hpp>
//#include <ModelObject.hpp>
//#include <Model.hpp>
//#include <Shader.hpp>
//#include <TransformComponent.hpp>
//#include <ShaderComponent.hpp>
//#include <PhysicsComponent.hpp>
//#include <AudioComponent.hpp>
//
//#include <JsonParser.hpp>
//
//using namespace std;
//using namespace Spore;
//
//enum class JsonType
//{
//	Object,
//	Array,
//	String,
//	Number,
//	True,
//	False,
//	Null
//};
//
//class JsonValue
//{
//public:
//	JsonType type;
//	string stringValue;
//	float numberValue;
//	vector<JsonValue> arrayValue;
//	map<string, JsonValue> objectValue;
//};
//
//class JsonParser
//{
//public:
//	JsonValue parse(const string& jsonStr)
//	{
//		index = 0;
//		return parseValue(jsonStr);
//	}
//
//private:
//	int index;
//	JsonValue parseValue(const string& jsonStr)
//	{
//		skipWhilespace(jsonStr);
//		char ch = jsonStr [index];
//		if (ch == '{')
//		{
//			return parseObject(jsonStr);
//		}
//		else if (ch == '[')
//		{
//			return parseArray(jsonStr);
//		}
//		else if (ch == '"')
//		{
//			return parseString(jsonStr);
//		}
//		else if (isdigit(ch) || ch == '-')
//		{
//			return parseNumber(jsonStr);
//		}
//		else if (jsonStr.substr(index, 4) == "true")
//		{
//			index += 4;
//		}
//		else if (jsonStr.substr(index, 5) == "false")
//		{
//			index += 5;
//		}
//		else if (jsonStr.substr(index, 4) == "null")
//		{
//			index += 4;
//			return{ JsonType::Null };
//		}
//		throw runtime_error("Invalid JSON");
//	}
//
//	JsonValue parseObject(const string& jsonStr)
//	{
//		JsonValue obj;
//		index++;
//		while (jsonStr [index] != '}')
//		{
//			skipWhilespace(jsonStr);
//			string key = parseString(jsonStr).stringValue;
//			skipWhilespace(jsonStr);
//			if (jsonStr [index] != ':')
//			{
//				throw runtime_error("Expected colon in object");
//			}
//			index++;
//			JsonValue value = parseValue(jsonStr);
//			obj.objectValue [key] = value;
//			skipWhilespace(jsonStr);
//			if (jsonStr [index] == ',')
//			{
//				index++;
//			}
//			else if (jsonStr [index] != '}')
//			{
//				throw runtime_error("Expedted comma or closing brace in object");
//			}
//		}
//		index++;
//		obj.type = JsonType::Object;
//		return obj;
//	}
//
//	JsonValue parseArray(const string& jsonStr)
//	{
//		JsonValue arr;
//		index++;
//		while (jsonStr [index] != ']')
//		{
//			skipWhilespace(jsonStr);
//			arr.arrayValue.push_back(parseValue(jsonStr));
//			skipWhilespace(jsonStr);
//			if (jsonStr [index] == ',')
//			{
//				index++;
//			}
//			else if (jsonStr [index] != ']')
//			{
//				throw runtime_error("Expected comma or closing bracked in array");
//			}
//		}
//		index++;
//		arr.type = JsonType::Array;
//		return arr;
//	}
//
//	JsonValue parseString(const string& jsonStr)
//	{
//		JsonValue str;
//		index++;
//		int start = index;
//		while (jsonStr [index] != '"')
//		{
//			if (jsonStr [index] == '\\')
//			{
//				index += 2;
//			}
//			else
//			{
//				index++;
//			}
//		}
//		str.stringValue = jsonStr.substr(start, index - start);
//		index++;
//		str.type = JsonType::String;
//		return str;
//	}
//
//	JsonValue parseNumber(const string& jsonStr)
//	{
//		JsonValue num;
//		int start = index;
//		while (isdigit(jsonStr [index]) || jsonStr [index] == '.' || jsonStr[index] == '-')
//		{
//			index++;
//		}
//		string numStr = jsonStr.substr(start, index - start);
//		num.numberValue = stod(numStr);
//		num.type = JsonType::Number;
//		return num;
//	}
//
//	void skipWhilespace(const string& jsonStr)
//	{
//		while (isspace(jsonStr [index]))
//		{
//			index++;
//		}
//	}
//};
//
//void printJsonValue(const JsonValue& jsonValue, int depth = 0)
//{
//	switch (jsonValue.type)
//	{
//		case JsonType::Object:
//			cout << "{\n";
//			for (const auto& pair : jsonValue.objectValue)
//			{
//				cout << string(depth + 1, '\t') << "\"" << pair.first << "\": ";
//				printJsonValue(pair.second, depth + 1);
//				cout << ",\n";
//			}
//			cout << string(depth, '\t') << "}";
//			break;
//		case JsonType::Array:
//			cout << "[\n";
//			for (const auto& value : jsonValue.arrayValue)
//			{
//				cout << string(depth + 1, '\t');
//				printJsonValue(value, depth + 1);
//				cout << ",\n";
//			}
//			cout << string(depth, '\t') << "]";
//			break;
//		case JsonType::String:
//			cout << "\"" << jsonValue.stringValue << "\"";
//			break;
//		case JsonType::Number:
//			cout << jsonValue.numberValue;
//			break;
//		case JsonType::True:
//			cout << "true";
//			break;
//		case JsonType::False:
//			cout << "false";
//			break;
//		case JsonType::Null:
//			cout << "null";
//			break;
//	}
//}
//
//int JsonParserTest::runtest()
//{
//	ifstream file("./Assets/Configs/config.json");
//	if (!file.is_open())
//	{
//		cout << "Failed to open file" << endl;
//		return 1;
//	}
//
//	string jsonStr((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
//
//	JsonParser parser;
//	try
//	{
//		JsonValue jsonValue = parser.parse(jsonStr);
//		printJsonValue(jsonValue);
//		cout << endl;
//
//		string formatVersion = jsonValue.objectValue.find("format_version")->second.stringValue;
//		vector<Scene*> scenes;
//		for (const auto& sceneValue : jsonValue.objectValue.find("scenes")->second.arrayValue)
//		{
//			Scene* scene = new Scene(sceneValue.objectValue.begin()->first);
//
//			for (const auto& objectValue : sceneValue.objectValue.begin()->second.objectValue.find("objects")->second.arrayValue)
//			{
//				Object* object = nullptr;
//				if (objectValue.objectValue.begin()->second.objectValue.find("type")->second.stringValue == "model")
//				{
//					string identifier = objectValue.objectValue.begin()->first;
//					object = new ModelObject(identifier);
//				}
//				else if (objectValue.objectValue.begin()->second.objectValue.find("type")->second.stringValue == "light")
//				{
//					string identifier = objectValue.objectValue.begin()->first;
//					object = new Light(identifier);
//				}
//				const auto& components = objectValue.objectValue.begin()->second.objectValue.find("components")->second.arrayValue;
//				for (const auto& componentValue : components)
//				{
//					const auto& componentName = componentValue.objectValue.begin()->first;
//					std::unordered_map<std::string, Component*> components = object->GetComponents();
//					if (componentName == "transform")
//					{
//						TransformComponent* transformComponent = dynamic_cast<TransformComponent*>(components.find("Transform")->second);
//						vec3f position(0.0f), rotation(0.0f), scale(1.0f);
//						const auto& properties = componentValue.objectValue.begin()->second.objectValue.find("properties")->second.arrayValue [0].objectValue;
//						for (const auto& propertyi : properties)
//						{
//							const auto& propertyName = propertyi.first;
//							const auto& propertyValue = propertyi.second.arrayValue;
//							if (propertyName == "transform")
//							{
//								position.x = propertyValue [0].objectValue.find("position")->second.arrayValue [0].numberValue;
//								rotation.x = propertyValue [1].objectValue.find("rotation")->second.arrayValue [0].numberValue;
//								scale.x = propertyValue [2].objectValue.find("scale")->second.arrayValue [0].numberValue;
//								position.y = propertyValue [0].objectValue.find("position")->second.arrayValue [1].numberValue;
//								rotation.y = propertyValue [1].objectValue.find("rotation")->second.arrayValue [1].numberValue;
//								scale.y = propertyValue [2].objectValue.find("scale")->second.arrayValue [1].numberValue;
//								position.z = propertyValue [0].objectValue.find("position")->second.arrayValue [2].numberValue;
//								rotation.z = propertyValue [1].objectValue.find("rotation")->second.arrayValue [2].numberValue;
//								scale.z = propertyValue [2].objectValue.find("scale")->second.arrayValue [2].numberValue;
//							}
//						}
//						transformComponent->SetPosition(position);
//						transformComponent->SetRotation(rotation);
//						transformComponent->SetScale(scale);
//					}
//					else if (componentName == "shader")
//					{
//						const auto& properties = componentValue.objectValue.begin()->second.objectValue.find("properties")->second.arrayValue [0].objectValue.find("shaders")->second.arrayValue;
//						for (const auto& shaderValue : properties)
//						{
//							string identifier = shaderValue.objectValue.begin()->first;
//						}
//					}
//					else if (componentName == "physics")
//					{
//						const auto& properties = componentValue.objectValue.begin()->second.objectValue.find("properties")->second.arrayValue [0].objectValue;
//						vec3f position, rotation, scale;
//						for (const auto& propertyi : properties)
//						{
//							const auto& propertyName = propertyi.first;
//							const auto& propertyValue = propertyi.second.arrayValue;
//							position.x = propertyValue [0].objectValue.find("position")->second.arrayValue [0].numberValue;
//							rotation.x = propertyValue [1].objectValue.find("rotation")->second.arrayValue [0].numberValue;
//							scale.x = propertyValue [2].objectValue.find("scale")->second.arrayValue [0].numberValue;
//							position.y = propertyValue [0].objectValue.find("position")->second.arrayValue [1].numberValue;
//							rotation.y = propertyValue [1].objectValue.find("rotation")->second.arrayValue [1].numberValue;
//							scale.y = propertyValue [2].objectValue.find("scale")->second.arrayValue [1].numberValue;
//							position.z = propertyValue [0].objectValue.find("position")->second.arrayValue [2].numberValue;
//							rotation.z = propertyValue [1].objectValue.find("rotation")->second.arrayValue [2].numberValue;
//							scale.z = propertyValue [2].objectValue.find("scale")->second.arrayValue [2].numberValue;
//						}
//					}
//					else if (componentName == "audio")
//					{
//						const auto& properties = componentValue.objectValue.begin()->second.objectValue.find("properties")->second.arrayValue [0].objectValue;
//						for (const auto& propertyi : properties)
//						{
//
//						}
//						string buffer = componentValue.objectValue.begin()->second.objectValue.find("properties")->second.arrayValue [0].objectValue.find("buffer")->second.stringValue;
//						string source = componentValue.objectValue.begin()->second.objectValue.find("properties")->second.arrayValue [1].objectValue.find("source")->second.stringValue;
//					}
//				}
//				scene->m_object_mapper.insert(std::make_pair(object->m_identifier, object));
//			}
//			scenes.push_back(scene);
//		}
//	}
//	catch (const exception& e)
//	{
//		cout << "Error: " << e.what() << endl;
//	}
//	return 0;
//}
//
//int main2()
//{
//	ifstream file("./Assets/Configs/config.json");
//	if (!file.is_open())
//	{
//		cout << "Failed to open file" << endl;
//		return 1;
//	}
//
//	string jsonStr((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
//
//	JsonParser parser;
//	try
//	{
//		JsonValue jsonValue = parser.parse(jsonStr);
//		printJsonValue(jsonValue);
//		cout << endl;
//
//		string formatVersion = jsonValue.objectValue.find("format_version")->second.stringValue;
//		vector<Scene*> scenes;
//		for (const auto& sceneValue : jsonValue.objectValue.find("scenes")->second.arrayValue)
//		{
//			Scene* scene = new Scene(sceneValue.objectValue.begin()->first);
//
//			for (const auto& objectValue : sceneValue.objectValue.begin()->second.objectValue.find("objects")->second.arrayValue)
//			{
//				Object* object = nullptr;
//				if (objectValue.objectValue.begin()->second.objectValue.find("type")->second.stringValue == "model")
//				{
//					string identifier = objectValue.objectValue.begin()->first;
//					object = new ModelObject(identifier);
//				}
//				else if (objectValue.objectValue.begin()->second.objectValue.find("type")->second.stringValue == "light")
//				{
//					string identifier = objectValue.objectValue.begin()->first;
//					object = new Light(identifier);
//				}
//				const auto& components = objectValue.objectValue.begin()->second.objectValue.find("components")->second.arrayValue;
//				for (const auto& componentValue : components)
//				{
//					const auto& componentName = componentValue.objectValue.begin()->first;
//					std::unordered_map<std::string, Component*> components = object->GetComponents();
//					if (componentName == "transform")
//					{
//						TransformComponent* transformComponent = dynamic_cast<TransformComponent*>(components.find("Transform")->second);
//						vec3f position, rotation, scale;
//						const auto& properties = componentValue.objectValue.begin()->second.objectValue.find("properties")->second.arrayValue [0].objectValue;
//						for (const auto& propertyi : properties)
//						{
//							const auto& propertyValue = propertyi.second.arrayValue [0].arrayValue;
//							for (int i = 0; i < 3; ++i)
//							{
//								position [i] = std::stof(propertyValue [3].arrayValue [i].stringValue);
//								rotation [i] = std::stof(propertyValue [4].arrayValue [i].stringValue);
//								scale [i] = std::stof(propertyValue [5].arrayValue [i].stringValue);
//							}
//						}
//						transformComponent->SetPosition(position);
//						transformComponent->SetRotation(rotation);
//						transformComponent->SetScale(scale);
//					}
//					else if (componentName == "shader")
//					{
//						const auto& properties = componentValue.objectValue.begin()->second.objectValue.find("properties")->second.arrayValue [0].objectValue.find("shaders")->second.arrayValue;
//						for (const auto& shaderValue : properties)
//						{
//							string identifier = shaderValue.objectValue.begin()->first;
//						}
//					}
//					else if (componentName == "physics")
//					{
//						const auto& properties = componentValue.objectValue.begin()->second.objectValue.find("properties")->second.arrayValue [0].objectValue;
//						vec3f position, rotation, scale;
//						for (const auto& propertyi : properties)
//						{
//							const auto& propertyName = propertyi.first;
//							const auto& propertyValue = propertyi.second.arrayValue [0].arrayValue;
//							for (int i = 0; i < 3; ++i)
//							{
//								position [i] = std::stof(propertyValue [0].arrayValue [i].stringValue);
//								rotation [i] = std::stof(propertyValue [1].arrayValue [i].stringValue);
//								scale [i] = std::stof(propertyValue [2].arrayValue [i].stringValue);
//							}
//						}
//					}
//					else if (componentName == "audio")
//					{
//						string buffer = componentValue.objectValue.begin()->second.objectValue.find("properties")->second.arrayValue [0].objectValue.find("source")->second.stringValue;
//						string source = componentValue.objectValue.begin()->second.objectValue.find("properties")->second.arrayValue [1].objectValue.find("source")->second.stringValue;
//					}
//				}
//				scene->m_object_mapper.insert(std::make_pair(object->m_identifier, object));
//			}
//			scenes.push_back(scene);
//		}
//	}
//	catch (const exception& e)
//	{
//		cout << "Error: " << e.what() << endl;
//	}
//	return 0;
//}