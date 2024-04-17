#include <JsonParser.hpp>

using namespace std;
using namespace Spore;

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
	JsonType type;
	string stringValue;
	float numberValue;
	vector<JsonValue> arrayValue;
	map<string, JsonValue> objectValue;
};

class JsonParser
{
public:
	JsonValue parse(const string& jsonStr)
	{
		index = 0;
		return parseValue(jsonStr);
	}

private:
	int index;
	JsonValue parseValue(const string& jsonStr)
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
			return{ JsonType::Null };
		}
		throw runtime_error("Invalid JSON");
	}

	JsonValue parseObject(const string& jsonStr)
	{
		JsonValue obj;
		index++;
		while (jsonStr [index] != '}')
		{
			skipWhilespace(jsonStr);
			string key = parseString(jsonStr).stringValue;
			skipWhilespace(jsonStr);
			if (jsonStr [index] != ':')
			{
				throw runtime_error("Expected colon in object");
			}
			index++;
			JsonValue value = parseValue(jsonStr);
			obj.objectValue [key] = value;
			skipWhilespace(jsonStr);
			if (jsonStr [index] == ',')
			{
				index++;
			}
			else if (jsonStr [index] != '}')
			{
				throw runtime_error("Expedted comma or closing brace in object");
			}
		}
		index++;
		obj.type = JsonType::Object;
		return obj;
	}

	JsonValue parseArray(const string& jsonStr)
	{
		JsonValue arr;
		index++;
		while (jsonStr [index] != ']')
		{
			skipWhilespace(jsonStr);
			arr.arrayValue.push_back(parseValue(jsonStr));
			skipWhilespace(jsonStr);
			if (jsonStr [index] == ',')
			{
				index++;
			}
			else if (jsonStr [index] != ']')
			{
				throw runtime_error("Expected comma or closing bracked in array");
			}
		}
		index++;
		arr.type = JsonType::Array;
		return arr;
	}

	JsonValue parseString(const string& jsonStr)
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
		str.stringValue = jsonStr.substr(start, index - start);
		index++;
		str.type = JsonType::String;
		return str;
	}

	JsonValue parseNumber(const string& jsonStr)
	{
		JsonValue num;
		int start = index;
		while (isdigit(jsonStr [index]) || jsonStr [index] == '.' || jsonStr[index] == '-')
		{
			index++;
		}
		string numStr = jsonStr.substr(start, index - start);
		num.numberValue = (float32) stod(numStr);
		num.type = JsonType::Number;
		return num;
	}

	void skipWhilespace(const string& jsonStr)
	{
		while (isspace(jsonStr [index]))
		{
			index++;
		}
	}
};

void printJsonValue(const JsonValue& jsonValue, int depth = 0)
{
	switch (jsonValue.type)
	{
		case JsonType::Object:
			cout << "{\n";
			for (const auto& pair : jsonValue.objectValue)
			{
				cout << string(depth + 1, '\t') << "\"" << pair.first << "\": ";
				printJsonValue(pair.second, depth + 1);
				cout << ",\n";
			}
			cout << string(depth, '\t') << "}";
			break;
		case JsonType::Array:
			cout << "[\n";
			for (const auto& value : jsonValue.arrayValue)
			{
				cout << string(depth + 1, '\t');
				printJsonValue(value, depth + 1);
				cout << ",\n";
			}
			cout << string(depth, '\t') << "]";
			break;
		case JsonType::String:
			cout << "\"" << jsonValue.stringValue << "\"";
			break;
		case JsonType::Number:
			cout << jsonValue.numberValue;
			break;
		case JsonType::True:
			cout << "true";
			break;
		case JsonType::False:
			cout << "false";
			break;
		case JsonType::Null:
			cout << "null";
			break;
	}
}

int JsonParserTest::runtest(const char* p_path, PhysicSystem* p_physic_system)
{
	ifstream file(p_path);
	if (!file.is_open())
	{
		cout << "Failed to open file" << endl;
		return 1;
	}

	string jsonStr((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());

	JsonParser parser;
	try
	{
		JsonValue jsonValue = parser.parse(jsonStr);
		printJsonValue(jsonValue);
		cout << endl;

		string formatVersion = jsonValue.objectValue.find("format_version")->second.stringValue;
		//vector<Scene*> scenes;
		for (const auto& sceneValue : jsonValue.objectValue.find("scenes")->second.arrayValue)
		{
			std::string sceneIdentifier = sceneValue.objectValue.begin()->second.objectValue.find("identifier")->second.stringValue;
			Scene* scene = new Scene(sceneIdentifier);
			p_physic_system->AddScene(scene);

			for (const auto& objectValue : sceneValue.objectValue.begin()->second.objectValue.find("objects")->second.arrayValue)
			{
				Object* object = nullptr;
				if (objectValue.objectValue.begin()->second.objectValue.find("type")->second.stringValue == "model")
				{
					std::string identifier = objectValue.objectValue.begin()->second.objectValue.find("identifier")->second.stringValue;
					object = new ModelObject(identifier);
				}
				else if (objectValue.objectValue.begin()->second.objectValue.find("type")->second.stringValue == "light")
				{
					string identifier = objectValue.objectValue.begin()->first;
					object = new Light(identifier);
				}
				const auto& componentValue = objectValue.objectValue.begin()->second.objectValue.find("components")->second.objectValue;

				std::unordered_map<std::string, Component*> components = object->GetComponents();

				// Transform component
				const auto& transformComponentValue = componentValue.find("transform");
				TransformComponent* transformComponent = dynamic_cast<TransformComponent*>(components.find("Transform")->second);
				vec3f position(0.0f), rotation(0.0f), scale(1.0f);
				const auto& transformComponentProperties = transformComponentValue->second.objectValue.find("properties");

				const auto& transformTransformProperty = transformComponentProperties->second.objectValue.find("transform");

				const auto& positionTransformTransformProperty = transformTransformProperty->second.objectValue.find("position")->second.arrayValue;
				position.x = positionTransformTransformProperty [0].numberValue;
				position.y = positionTransformTransformProperty [1].numberValue;
				position.z = positionTransformTransformProperty [2].numberValue;
				const auto& rotationTransformTransformProperty = transformTransformProperty->second.objectValue.find("rotation")->second.arrayValue;
				rotation.x = rotationTransformTransformProperty [0].numberValue;
				rotation.y = rotationTransformTransformProperty [1].numberValue;
				rotation.z = rotationTransformTransformProperty [2].numberValue;
				const auto& scaleTransformTransformProperty = transformTransformProperty->second.objectValue.find("scale")->second.arrayValue;
				scale.x = scaleTransformTransformProperty [0].numberValue;
				scale.y = scaleTransformTransformProperty [1].numberValue;
				scale.z = scaleTransformTransformProperty [2].numberValue;
				
				transformComponent->SetPosition(position);
				transformComponent->SetRotation(rotation);
				transformComponent->SetScale(scale);

				// Shader component
				const auto& shaderComponentValue = componentValue.find("shader");
				const auto& shaderComponentProperties = shaderComponentValue->second.objectValue.find("properties");

				const auto& shaderProperty = shaderComponentProperties->second.objectValue.find("shaders");
				//std::string shaderIdentifier = shaderProperty->second.objectValue.find("identifier")->second.stringValue;

				// Physics component
				const auto& physicsComponentValue = componentValue.find("physics");
				PhysicsComponent* physicsComponent = dynamic_cast<PhysicsComponent*>(components.find("Physics")->second);
				ModelObject* modelObject = dynamic_cast<ModelObject*>(object);
				const auto& physicsComponentProperties = physicsComponentValue->second.objectValue.find("properties");

				const auto& physicsTransformProperty = physicsComponentProperties->second.objectValue.find("transform");

				const auto& positionPhysicsTransformProperty = physicsTransformProperty->second.objectValue.find("position")->second.arrayValue;
				position.x = positionPhysicsTransformProperty [0].numberValue;
				position.y = positionPhysicsTransformProperty [1].numberValue;
				position.z = positionPhysicsTransformProperty [2].numberValue;
				const auto& rotationPhysicsTransformProperty = physicsTransformProperty->second.objectValue.find("rotation")->second.arrayValue;
				rotation.x = rotationPhysicsTransformProperty [0].numberValue;
				rotation.y = rotationPhysicsTransformProperty [1].numberValue;
				rotation.z = rotationPhysicsTransformProperty [2].numberValue;
				const auto& scalePhysicsTransformProperty = physicsTransformProperty->second.objectValue.find("scale")->second.arrayValue;
				scale.x = scalePhysicsTransformProperty [0].numberValue;
				scale.y = scalePhysicsTransformProperty [1].numberValue;
				scale.z = scalePhysicsTransformProperty [2].numberValue;

				const auto& physicsModelShapeProperty = physicsComponentProperties->second.objectValue.find("model_type")->second.stringValue;
				JPH::RefConst<JPH::Shape> modelShape;
				if (physicsModelShapeProperty == "CUBE")
				{
					modelObject->SetModelType(ModelType::CUBE);
				}
				else if (physicsModelShapeProperty == "SPHERE")
				{
					modelObject->SetModelType(ModelType::SPHERE);
				}
				else if (physicsModelShapeProperty == "CAPSULE")
				{
					modelObject->SetModelType(ModelType::CAPSULE);
				}
				else if (physicsModelShapeProperty == "CYLINDER")
				{
					modelObject->SetModelType(ModelType::CYLINDER);
				}
				else if (physicsModelShapeProperty == "PLANE")
				{
					modelObject->SetModelType(ModelType::PLANE);
				}
				else if (physicsModelShapeProperty == "QUAD")
				{
					modelObject->SetModelType(ModelType::QUAD);
				}

				const auto& physicsMotionTypeProperty = physicsComponentProperties->second.objectValue.find("motion_type")->second.stringValue;
				JPH::EMotionType motionType = JPH::EMotionType::Dynamic;
				if (physicsMotionTypeProperty == "Dynamic")
				{
					motionType = JPH::EMotionType::Dynamic;
				}
				else if (physicsMotionTypeProperty == "Kinematic")
				{
					motionType = JPH::EMotionType::Kinematic;
				}
				else if (physicsMotionTypeProperty == "Static")
				{
					motionType = JPH::EMotionType::Static;
				}

				const auto& physicsActivationProperty = physicsComponentProperties->second.objectValue.find("activation")->second.stringValue;
				JPH::EActivation activation = JPH::EActivation::DontActivate;
				if (physicsActivationProperty == "DontActivate")
				{
					activation = JPH::EActivation::DontActivate;
				}
				else if (physicsActivationProperty == "Activate")
				{
					activation = JPH::EActivation::Activate;
				}

				// Audio component
				const auto& audioComponentValue = componentValue.find("audio");
				const auto& audioComponentProperties = audioComponentValue->second.objectValue.find("properties");


				const auto& modelsValue = objectValue.objectValue.begin()->second.objectValue.find("models")->second.objectValue;
				const auto& modelvalue = modelsValue.find("model")->second.objectValue;
				const auto& modelIdentifier = modelvalue.find("identifier")->second.stringValue;
				const auto& modelPath = modelvalue.find("path")->second.stringValue;
				Model* model = new Model(modelPath);
				modelObject->AddModel(model);

				scene->AddObject(object);
				physicsComponent->GetBodyInterface()->SetMotionType(physicsComponent->GetBody()->GetID(), motionType, activation);
				//object->AddObserver(scene);
			}
			scenes.push_back(scene);
		}
	}
	catch (const exception& e)
	{
		cout << "Error: " << e.what() << endl;
	}
	return 0;
}

int main2()
{
	ifstream file("./Assets/Configs/config.json");
	if (!file.is_open())
	{
		cout << "Failed to open file" << endl;
		return 1;
	}

	string jsonStr((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());

	JsonParser parser;
	try
	{
		JsonValue jsonValue = parser.parse(jsonStr);
		printJsonValue(jsonValue);
		cout << endl;

		string formatVersion = jsonValue.objectValue.find("format_version")->second.stringValue;
		vector<Scene*> scenes;
		for (const auto& sceneValue : jsonValue.objectValue.find("scenes")->second.arrayValue)
		{
			Scene* scene = new Scene(sceneValue.objectValue.begin()->first);

			for (const auto& objectValue : sceneValue.objectValue.begin()->second.objectValue.find("objects")->second.arrayValue)
			{
				Object* object = nullptr;
				if (objectValue.objectValue.begin()->second.objectValue.find("type")->second.stringValue == "model")
				{
					string identifier = objectValue.objectValue.begin()->first;
					object = new ModelObject(identifier);
				}
				else if (objectValue.objectValue.begin()->second.objectValue.find("type")->second.stringValue == "light")
				{
					string identifier = objectValue.objectValue.begin()->first;
					object = new Light(identifier);
				}
				const auto& components = objectValue.objectValue.begin()->second.objectValue.find("components")->second.arrayValue;
				for (const auto& componentValue : components)
				{
					const auto& componentName = componentValue.objectValue.begin()->first;
					std::unordered_map<std::string, Component*> components = object->GetComponents();
					if (componentName == "transform")
					{
						TransformComponent* transformComponent = dynamic_cast<TransformComponent*>(components.find("Transform")->second);
						vec3f position, rotation, scale;
						const auto& properties = componentValue.objectValue.begin()->second.objectValue.find("properties")->second.arrayValue [0].objectValue;
						for (const auto& propertyi : properties)
						{
							const auto& propertyValue = propertyi.second.arrayValue [0].arrayValue;
							for (int i = 0; i < 3; ++i)
							{
								position [i] = std::stof(propertyValue [3].arrayValue [i].stringValue);
								rotation [i] = std::stof(propertyValue [4].arrayValue [i].stringValue);
								scale [i] = std::stof(propertyValue [5].arrayValue [i].stringValue);
							}
						}
						transformComponent->SetPosition(position);
						transformComponent->SetRotation(rotation);
						transformComponent->SetScale(scale);
					}
					else if (componentName == "shader")
					{
						const auto& properties = componentValue.objectValue.begin()->second.objectValue.find("properties")->second.arrayValue [0].objectValue.find("shaders")->second.arrayValue;
						for (const auto& shaderValue : properties)
						{
							string identifier = shaderValue.objectValue.begin()->first;
						}
					}
					else if (componentName == "physics")
					{
						const auto& properties = componentValue.objectValue.begin()->second.objectValue.find("properties")->second.arrayValue [0].objectValue;
						vec3f position, rotation, scale;
						for (const auto& propertyi : properties)
						{
							const auto& propertyName = propertyi.first;
							const auto& propertyValue = propertyi.second.arrayValue [0].arrayValue;
							for (int i = 0; i < 3; ++i)
							{
								position [i] = std::stof(propertyValue [0].arrayValue [i].stringValue);
								rotation [i] = std::stof(propertyValue [1].arrayValue [i].stringValue);
								scale [i] = std::stof(propertyValue [2].arrayValue [i].stringValue);
							}
						}
					}
					else if (componentName == "audio")
					{
						string buffer = componentValue.objectValue.begin()->second.objectValue.find("properties")->second.arrayValue [0].objectValue.find("source")->second.stringValue;
						string source = componentValue.objectValue.begin()->second.objectValue.find("properties")->second.arrayValue [1].objectValue.find("source")->second.stringValue;
					}
				}
				scene->m_object_mapper.insert(std::make_pair(object->m_identifier, object));
			}
			scenes.push_back(scene);
		}
	}
	catch (const exception& e)
	{
		cout << "Error: " << e.what() << endl;
	}
	return 0;
}