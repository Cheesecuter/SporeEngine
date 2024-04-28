#include <Serializer.hpp>
#include <AudioComponent.hpp>
#include <CameraComponent.hpp>
#include <CharacterControllerComponent.hpp>
#include <LightComponent.hpp>
#include <ModelComponent.hpp>
#include <PhysicsComponent.hpp>
#include <ShaderComponent.hpp>
#include <TransformComponent.hpp>
#include <ConsoleLogger.hpp>

namespace Spore
{
	void printJsonValue(const JsonValue& jsonValue, int depth = 0);

	Serializer::Serializer()
	{

	}

	Serializer::~Serializer()
	{

	}

	int Serializer::Serialize(const char* p_path)
	{
		std::ofstream file(p_path);
		if (!file.is_open())
		{
			ConsoleLogger::GetInstance().Logger()->error("Serializer::Serialize: Failed to open file at path {}", p_path);
			return 1;
		}

		JsonParser parser;
		try
		{
			JsonValue root;

			root.m_object_value ["format_version"] = JsonValue("0.0.1");

			std::vector<JsonValue> scenesArray;

			for (const auto it_scene : m_scenes)
			{
				JsonValue sceneObject;
				sceneObject.m_type = JsonType::Object;
				sceneObject.m_object_value ["identifier"] = JsonValue(it_scene->m_identifier);

				std::vector<JsonValue> objectsArray;

				for (std::pair<std::string, Object*> it_object : it_scene->m_object_mapper)
				{
					JsonValue objectObject;
					objectObject.m_type = JsonType::Object;
					objectObject.m_object_value ["identifier"] = JsonValue(it_object.second->m_identifier);
					std::string objectType = it_object.second->m_type;
					objectObject.m_object_value ["type"] = JsonValue(objectType);
					JsonValue objectComponentObject;
					objectComponentObject.m_type = JsonType::Object;

					// Transform Component
					TransformComponent* transformComponent = dynamic_cast<TransformComponent*>(it_object.second->GetComponent("Transform"));
					if (transformComponent != nullptr)
					{
						JsonValue transformComponentObject;
						transformComponentObject.m_type = JsonType::Object;
						transformComponentObject.m_object_value ["name"] = JsonValue("Transform");
						JsonValue transformComponentPropertiesObject;
						transformComponentPropertiesObject.m_type = JsonType::Object;

						std::vector<JsonValue> transformComponentPropertyPositionArray;
						JsonValue transformComponentPropertyPositionNumber;
						transformComponentPropertyPositionNumber.m_type = JsonType::Number;
						vec3f transformPosition = transformComponent->GetPosition();
						transformComponentPropertyPositionNumber.m_number_value = transformPosition.x;
						transformComponentPropertyPositionArray.push_back(transformComponentPropertyPositionNumber);
						transformComponentPropertyPositionNumber.m_number_value = transformPosition.y;
						transformComponentPropertyPositionArray.push_back(transformComponentPropertyPositionNumber);
						transformComponentPropertyPositionNumber.m_number_value = transformPosition.z;
						transformComponentPropertyPositionArray.push_back(transformComponentPropertyPositionNumber);
						transformComponentObject.m_object_value ["properties"].m_object_value ["transform"].m_object_value ["position"] = transformComponentPropertyPositionArray;
						transformComponentObject.m_object_value ["properties"].m_object_value ["transform"].m_object_value ["position"].m_type = JsonType::Array;

						std::vector<JsonValue> transformComponentPropertyRotationArray;
						JsonValue transformComponentPropertyRotationNumber;
						transformComponentPropertyRotationNumber.m_type = JsonType::Number;
						vec3f transformRotation = transformComponent->GetRotation();
						transformComponentPropertyRotationNumber.m_number_value = transformRotation.x;
						transformComponentPropertyRotationArray.push_back(transformComponentPropertyRotationNumber);
						transformComponentPropertyRotationNumber.m_number_value = transformRotation.y;
						transformComponentPropertyRotationArray.push_back(transformComponentPropertyRotationNumber);
						transformComponentPropertyRotationNumber.m_number_value = transformRotation.z;
						transformComponentPropertyRotationArray.push_back(transformComponentPropertyRotationNumber);
						transformComponentObject.m_object_value ["properties"].m_object_value ["transform"].m_object_value ["rotation"] = transformComponentPropertyRotationArray;
						transformComponentObject.m_object_value ["properties"].m_object_value ["transform"].m_object_value ["rotation"].m_type = JsonType::Array;

						std::vector<JsonValue> transformComponentPropertyScaleArray;
						JsonValue transformComponentPropertyScaleNumber;
						transformComponentPropertyScaleNumber.m_type = JsonType::Number;
						vec3f transformScale = transformComponent->GetScale();
						transformComponentPropertyScaleNumber.m_number_value = transformScale.x;
						transformComponentPropertyScaleArray.push_back(transformComponentPropertyScaleNumber);
						transformComponentPropertyScaleNumber.m_number_value = transformScale.y;
						transformComponentPropertyScaleArray.push_back(transformComponentPropertyScaleNumber);
						transformComponentPropertyScaleNumber.m_number_value = transformScale.z;
						transformComponentPropertyScaleArray.push_back(transformComponentPropertyScaleNumber);
						transformComponentObject.m_object_value ["properties"].m_object_value ["transform"].m_object_value ["scale"] = transformComponentPropertyScaleArray;
						transformComponentObject.m_object_value ["properties"].m_object_value ["transform"].m_object_value ["scale"].m_type = JsonType::Array;

						transformComponentObject.m_object_value ["properties"].m_object_value ["transform"].m_type = JsonType::Object;

						transformComponentObject.m_object_value ["properties"].m_type = JsonType::Object;


						objectComponentObject.m_object_value ["transform"] = transformComponentObject;
					}

					// Shader Component
					ShaderComponent* shaderComponent = dynamic_cast<ShaderComponent*>(it_object.second->GetComponent("Shader"));
					if (shaderComponent != nullptr)
					{
						JsonValue shaderComponentObject;
						shaderComponentObject.m_type = JsonType::Object;
						shaderComponentObject.m_object_value ["name"] = JsonValue("Shader");

						std::vector<JsonValue> shaderComponentPropertyShaderArray;

						shaderComponentObject.m_object_value ["properties"].m_object_value ["shaders"].m_array_value = shaderComponentPropertyShaderArray;
						shaderComponentObject.m_object_value ["properties"].m_object_value ["shaders"].m_type = JsonType::Array;

						shaderComponentObject.m_object_value ["properties"].m_type = JsonType::Object;

						objectComponentObject.m_object_value ["shader"] = shaderComponentObject;
					}
					
					if (objectType == "Model")
					{
						ModelObject* modelObject = dynamic_cast<ModelObject*>(it_object.second);

						// Physics Component
						PhysicsComponent* physicsComponent = dynamic_cast<PhysicsComponent*>(it_object.second->GetComponent("Physics"));
						if (physicsComponent != nullptr)
						{
							JsonValue physicsComponentObject;
							physicsComponentObject.m_type = JsonType::Object;
							physicsComponentObject.m_object_value ["name"] = JsonValue("Physics");

							JsonValue physicsComponentPropertiesObject;
							physicsComponentPropertiesObject.m_type = JsonType::Object;

							std::vector<JsonValue> physicsComponentPropertyPositionArray;
							JsonValue physicsComponentPropertyPositionNumber;
							physicsComponentPropertyPositionNumber.m_type = JsonType::Number;
							vec3f physicsPosition = physicsComponent->GetPosition();
							physicsComponentPropertyPositionNumber.m_number_value = physicsPosition.x;
							physicsComponentPropertyPositionArray.push_back(physicsComponentPropertyPositionNumber);
							physicsComponentPropertyPositionNumber.m_number_value = physicsPosition.y;
							physicsComponentPropertyPositionArray.push_back(physicsComponentPropertyPositionNumber);
							physicsComponentPropertyPositionNumber.m_number_value = physicsPosition.z;
							physicsComponentPropertyPositionArray.push_back(physicsComponentPropertyPositionNumber);
							physicsComponentObject.m_object_value ["properties"].m_object_value ["transform"].m_object_value ["position"] = physicsComponentPropertyPositionArray;
							physicsComponentObject.m_object_value ["properties"].m_object_value ["transform"].m_object_value ["position"].m_type = JsonType::Array;

							std::vector<JsonValue> physicsComponentPropertyRotationArray;
							JsonValue physicsComponentPropertyRotationNumber;
							physicsComponentPropertyRotationNumber.m_type = JsonType::Number;
							vec3f physicsRotation = physicsComponent->GetRotation();
							physicsComponentPropertyRotationNumber.m_number_value = physicsRotation.x;
							physicsComponentPropertyRotationArray.push_back(physicsComponentPropertyRotationNumber);
							physicsComponentPropertyRotationNumber.m_number_value = physicsRotation.y;
							physicsComponentPropertyRotationArray.push_back(physicsComponentPropertyRotationNumber);
							physicsComponentPropertyRotationNumber.m_number_value = physicsRotation.z;
							physicsComponentPropertyRotationArray.push_back(physicsComponentPropertyRotationNumber);
							physicsComponentObject.m_object_value ["properties"].m_object_value ["transform"].m_object_value ["rotation"] = physicsComponentPropertyRotationArray;
							physicsComponentObject.m_object_value ["properties"].m_object_value ["transform"].m_object_value ["rotation"].m_type = JsonType::Array;

							std::vector<JsonValue> physicsComponentPropertyScaleArray;
							JsonValue physicsComponentPropertyScaleNumber;
							physicsComponentPropertyScaleNumber.m_type = JsonType::Number;
							vec3f physicsScale = transformComponent->GetScale();
							physicsComponentPropertyScaleNumber.m_number_value = physicsScale.x;
							physicsComponentPropertyScaleArray.push_back(physicsComponentPropertyScaleNumber);
							physicsComponentPropertyScaleNumber.m_number_value = physicsScale.y;
							physicsComponentPropertyScaleArray.push_back(physicsComponentPropertyScaleNumber);
							physicsComponentPropertyScaleNumber.m_number_value = physicsScale.z;
							physicsComponentPropertyScaleArray.push_back(physicsComponentPropertyScaleNumber);
							physicsComponentObject.m_object_value ["properties"].m_object_value ["transform"].m_object_value ["scale"] = physicsComponentPropertyScaleArray;
							physicsComponentObject.m_object_value ["properties"].m_object_value ["transform"].m_object_value ["scale"].m_type = JsonType::Array;

							physicsComponentObject.m_object_value ["properties"].m_object_value ["transform"].m_type = JsonType::Object;

							std::string modelTypeStr = "";
							ModelType modelType = modelObject->GetModelType();
							if (modelType == ModelType::CUBE)
							{
								modelTypeStr = "CUBE";
							}
							else if (modelType == ModelType::SPHERE)
							{
								modelTypeStr = "SPHERE";
							}
							else if (modelType == ModelType::CAPSULE)
							{
								modelTypeStr = "CAPSULE";
							}
							else if (modelType == ModelType::CYLINDER)
							{
								modelTypeStr = "CYLINDER";
							}
							else if (modelType == ModelType::PLANE)
							{
								modelTypeStr = "PLANE";
							}
							else if (modelType == ModelType::QUAD)
							{
								modelTypeStr = "QUAD";
							}
							else if (modelType == ModelType::CUSTOM_CUBE)
							{
								modelTypeStr = "CUSTOM_CUBE";
							}
							else if (modelType == ModelType::CUSTOM_GIANT_FLOOR)
							{
								modelTypeStr = "CUSTOM_GIANT_FLOOR";
							}
							else if (modelType == ModelType::CUSTOM_GIANT_WALL)
							{
								modelTypeStr = "CUSTOM_GIANT_WALL";
							}
							else if (modelType == ModelType::CUSTOM_WALL)
							{
								modelTypeStr = "CUSTOM_WALL";
							}
							physicsComponentObject.m_object_value ["properties"].m_object_value ["model_type"] = JsonValue(modelTypeStr);

							std::string motionTypeStr = "";
							JPH::EMotionType motionType = physicsComponent->GetBodyInterface()->GetMotionType(physicsComponent->GetBody()->GetID());
							if (motionType == JPH::EMotionType::Dynamic)
							{
								motionTypeStr = "Dynamic";
							}
							else if (motionType == JPH::EMotionType::Kinematic)
							{
								motionTypeStr = "Kinematic";
							}
							else if (motionType == JPH::EMotionType::Static)
							{
								motionTypeStr = "Static";
							}
							physicsComponentObject.m_object_value ["properties"].m_object_value ["motion_type"] = JsonValue(motionTypeStr);

							std::string activationStr = "";
							if (physicsComponent->GetBodyInterface()->IsActive(physicsComponent->GetBody()->GetID()))
							{
								activationStr = "Activate";
							}
							else
							{
								activationStr = "DontActivate";
							}
							physicsComponentObject.m_object_value ["properties"].m_object_value ["activation"] = JsonValue(activationStr);

							std::vector<JsonValue> physicsComponentPropertyLinearVelocityArray;
							JsonValue physicsComponentPropertyLinearVelocityNumber;
							physicsComponentPropertyLinearVelocityNumber.m_type = JsonType::Number;
							vec3f physicsLinearVelocity = physicsComponent->GetLinearVelocity();
							physicsComponentPropertyLinearVelocityNumber.m_number_value = physicsLinearVelocity.x;
							physicsComponentPropertyLinearVelocityArray.push_back(physicsComponentPropertyLinearVelocityNumber);
							physicsComponentPropertyLinearVelocityNumber.m_number_value = physicsLinearVelocity.y;
							physicsComponentPropertyLinearVelocityArray.push_back(physicsComponentPropertyLinearVelocityNumber);
							physicsComponentPropertyLinearVelocityNumber.m_number_value = physicsLinearVelocity.z;
							physicsComponentPropertyLinearVelocityArray.push_back(physicsComponentPropertyLinearVelocityNumber);
							physicsComponentObject.m_object_value ["properties"].m_object_value ["velocity"].m_object_value ["linear_velocity"] = physicsComponentPropertyLinearVelocityArray;
							physicsComponentObject.m_object_value ["properties"].m_object_value ["velocity"].m_object_value ["linear_velocity"].m_type = JsonType::Array;

							std::vector<JsonValue> physicsComponentPropertyAngularVelocityArray;
							JsonValue physicsComponentPropertyAngularVelocityNumber;
							physicsComponentPropertyAngularVelocityNumber.m_type = JsonType::Number;
							vec3f physicsAngularVelocity = physicsComponent->GetAngularVelocity();
							physicsComponentPropertyAngularVelocityNumber.m_number_value = physicsAngularVelocity.x;
							physicsComponentPropertyAngularVelocityArray.push_back(physicsComponentPropertyAngularVelocityNumber);
							physicsComponentPropertyAngularVelocityNumber.m_number_value = physicsAngularVelocity.y;
							physicsComponentPropertyAngularVelocityArray.push_back(physicsComponentPropertyAngularVelocityNumber);
							physicsComponentPropertyAngularVelocityNumber.m_number_value = physicsAngularVelocity.z;
							physicsComponentPropertyAngularVelocityArray.push_back(physicsComponentPropertyAngularVelocityNumber);
							physicsComponentObject.m_object_value ["properties"].m_object_value ["velocity"].m_object_value ["angular_velocity"] = physicsComponentPropertyAngularVelocityArray;
							physicsComponentObject.m_object_value ["properties"].m_object_value ["velocity"].m_object_value ["angular_velocity"].m_type = JsonType::Array;

							physicsComponentObject.m_object_value ["properties"].m_object_value ["velocity"].m_type = JsonType::Object;

							float32 physicsGravityFactor = physicsComponent->GetGravityFactor();
							physicsComponentObject.m_object_value ["properties"].m_object_value ["gravity_factor"] = JsonValue(physicsGravityFactor);

							float32 physicsRestitution = physicsComponent->GetRestitution();
							physicsComponentObject.m_object_value ["properties"].m_object_value ["restitution"] = JsonValue(physicsRestitution);

							float32 physicsFriction = physicsComponent->GetFriction();
							physicsComponentObject.m_object_value ["properties"].m_object_value ["friction"] = JsonValue(physicsFriction);

							physicsComponentObject.m_object_value ["properties"].m_type = JsonType::Object;

							objectComponentObject.m_object_value ["physics"] = physicsComponentObject;
						}

						// Audio Component
						AudioComponent* audioComponent = dynamic_cast<AudioComponent*>(it_object.second->GetComponent("Audio"));
						
						if (audioComponent != nullptr)
						{
							JsonValue audioComponentObject;
							audioComponentObject.m_type = JsonType::Object;
							audioComponentObject.m_object_value ["name"] = JsonValue("Audio");

							audioComponentObject.m_object_value ["properties"].m_type = JsonType::Object;

							objectComponentObject.m_object_value ["audio"] = audioComponentObject;
						}

						CameraComponent* cameraComponent = dynamic_cast<CameraComponent*>(it_object.second->GetComponent("Camera"));
						if (cameraComponent != nullptr)
						{
							JsonValue cameraComponentObject;
							cameraComponentObject.m_type = JsonType::Object;
							cameraComponentObject.m_object_value ["name"] = JsonValue("Camera");

							cameraComponentObject.m_object_value ["properties"].m_type = JsonType::Object;

							objectComponentObject.m_object_value ["camera"] = cameraComponentObject;
						}

						CharacterControllerComponent* characterControllerComponent = dynamic_cast<CharacterControllerComponent*>(it_object.second->GetComponent("CharacterController"));
						if (characterControllerComponent != nullptr)
						{
							JsonValue characterControllerComponentObject;
							characterControllerComponentObject.m_type = JsonType::Object;
							characterControllerComponentObject.m_object_value ["name"] = JsonValue("CharacterController");

							characterControllerComponentObject.m_object_value ["properties"].m_type = JsonType::Object;

							objectComponentObject.m_object_value ["character_controller"] = characterControllerComponentObject;
						}
					}
					else if (objectType == "Light")
					{
						LightComponent* lightComponent = dynamic_cast<LightComponent*>(it_object.second->GetComponent("Light"));
						if (lightComponent != nullptr)
						{
							JsonValue lightComponentObject;
							lightComponentObject.m_type = JsonType::Object;
							lightComponentObject.m_object_value ["name"] = JsonValue("Light");

							lightComponentObject.m_object_value ["properties"].m_type = JsonType::Object;

							objectComponentObject.m_object_value ["light"] = lightComponentObject;
						}
					}
					objectObject.m_object_value ["components"] = objectComponentObject;

					if (objectType == "Model")
					{
						ModelObject* modelObject = dynamic_cast<ModelObject*>(it_object.second);

						JsonValue objectModelObject;
						objectModelObject.m_type = JsonType::Object;

						std::vector<JsonValue> modelsArray;
						Model* objectModel = modelObject->GetModel();
						JsonValue modelValue;
						modelValue.m_type = JsonType::Object;
						modelValue.m_object_value ["identifier"] = JsonValue(objectModel->m_identifier);
						modelValue.m_object_value ["path"] = JsonValue(objectModel->m_path);
						objectModelObject.m_object_value ["model"] = modelValue;

						objectObject.m_object_value ["models"] = objectModelObject;
					}


					objectsArray.push_back(objectObject);
				}
				sceneObject.m_object_value ["objects"].m_array_value = objectsArray;
				sceneObject.m_object_value ["objects"].m_type = JsonType::Array;
				scenesArray.push_back(sceneObject);
			}
			root.m_object_value ["scenes"].m_array_value = scenesArray;
			root.m_object_value ["scenes"].m_type = JsonType::Array;
			root.m_type = JsonType::Object;
			std::string jsonStr = parser.ToJsonString(root);
			file << jsonStr;
		}
		catch (const std::exception& e)
		{
			std::cout << "Error: " << e.what() << std::endl;
		}
		return 0;
	}

	int Serializer::Deserialize(const char* p_path)
	{
		std::ifstream file(p_path);
		if (!file.is_open())
		{
			ConsoleLogger::GetInstance().Logger()->error("Serializer::Serialize: Failed to open file at path {}", p_path);
			return 1;
		}

		std::string jsonStr((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

		JsonParser parser;
		try
		{
			m_json_value = parser.Parse(jsonStr);
			//printJsonValue(m_json_value);
			//std::cout << std::endl;

			std::string formatVersion = m_json_value.m_object_value.find("format_version")->second.m_string_value;
			for (const auto& sceneValue : m_json_value.m_object_value.find("scenes")->second.m_array_value)
			{
				std::string sceneIdentifier = sceneValue.m_object_value.find("identifier")->second.m_string_value;
				Scene* scene = new Scene(sceneIdentifier);
				m_physic_system->AddScene(scene);

				for (const auto& objectValue : sceneValue.m_object_value.find("objects")->second.m_array_value)
				{
					Object* object = nullptr;
					if (objectValue.m_object_value.find("type")->second.m_string_value == "Model")
					{
						std::string identifier = objectValue.m_object_value.find("identifier")->second.m_string_value;
						object = new ModelObject(identifier);
					}
					else if (objectValue.m_object_value.find("type")->second.m_string_value == "Light")
					{
						std::string identifier = objectValue.m_object_value.find("identifier")->second.m_string_value;
						object = new Light(identifier);
					}
					const auto& componentValue = objectValue.m_object_value.find("components")->second.m_object_value;

					std::unordered_map<std::string, Component*> components = object->GetComponents();

					// Transform component
					const auto& transformComponentValue = componentValue.find("transform");
					TransformComponent* transformComponent = dynamic_cast<TransformComponent*>(components.find("Transform")->second);
					vec3f position(0.0f), rotation(0.0f), scale(1.0f);
					const auto& transformComponentProperties = transformComponentValue->second.m_object_value.find("properties");

					const auto& transformTransformProperty = transformComponentProperties->second.m_object_value.find("transform");

					const auto& positionTransformTransformProperty = transformTransformProperty->second.m_object_value.find("position")->second.m_array_value;
					position.x = positionTransformTransformProperty [0].m_number_value;
					position.y = positionTransformTransformProperty [1].m_number_value;
					position.z = positionTransformTransformProperty [2].m_number_value;
					const auto& rotationTransformTransformProperty = transformTransformProperty->second.m_object_value.find("rotation")->second.m_array_value;
					rotation.x = rotationTransformTransformProperty [0].m_number_value;
					rotation.y = rotationTransformTransformProperty [1].m_number_value;
					rotation.z = rotationTransformTransformProperty [2].m_number_value;
					const auto& scaleTransformTransformProperty = transformTransformProperty->second.m_object_value.find("scale")->second.m_array_value;
					scale.x = scaleTransformTransformProperty [0].m_number_value;
					scale.y = scaleTransformTransformProperty [1].m_number_value;
					scale.z = scaleTransformTransformProperty [2].m_number_value;

					transformComponent->SetPosition(position);
					transformComponent->SetRotation(rotation);
					transformComponent->SetScale(scale);

					// Shader component
					const auto& shaderComponentValue = componentValue.find("shader");
					const auto& shaderComponentProperties = shaderComponentValue->second.m_object_value.find("properties");

					const auto& shaderProperty = shaderComponentProperties->second.m_object_value.find("shaders");
					//std::string shaderIdentifier = shaderProperty->second.objectValue.find("identifier")->second.stringValue;

					if (object->m_type == "Model")
					{
						ModelObject* modelObject = dynamic_cast<ModelObject*>(object);

						// Camera component
						const auto& cameraComponentValue = componentValue.find("camera");
						if (cameraComponentValue != componentValue.end())
						{
							CameraComponent* cameraComponent = new CameraComponent();
							modelObject->AddComponent(cameraComponent);
						}

						// CharacterController component
						const auto& characterControllerComponentValue = componentValue.find("character_controller");
						if (characterControllerComponentValue != componentValue.end())
						{
							CharacterControllerComponent* characterControllerComponent = new CharacterControllerComponent();
							modelObject->AddComponent(characterControllerComponent);
						}

						// Physics component
						const auto& physicsComponentValue = componentValue.find("physics");
						PhysicsComponent* physicsComponent = dynamic_cast<PhysicsComponent*>(components.find("Physics")->second);
						const auto& physicsComponentProperties = physicsComponentValue->second.m_object_value.find("properties");

						const auto& physicsTransformProperty = physicsComponentProperties->second.m_object_value.find("transform");

						const auto& positionPhysicsTransformProperty = physicsTransformProperty->second.m_object_value.find("position")->second.m_array_value;
						position.x = positionPhysicsTransformProperty [0].m_number_value;
						position.y = positionPhysicsTransformProperty [1].m_number_value;
						position.z = positionPhysicsTransformProperty [2].m_number_value;
						const auto& rotationPhysicsTransformProperty = physicsTransformProperty->second.m_object_value.find("rotation")->second.m_array_value;
						rotation.x = rotationPhysicsTransformProperty [0].m_number_value;
						rotation.y = rotationPhysicsTransformProperty [1].m_number_value;
						rotation.z = rotationPhysicsTransformProperty [2].m_number_value;
						const auto& scalePhysicsTransformProperty = physicsTransformProperty->second.m_object_value.find("scale")->second.m_array_value;
						scale.x = scalePhysicsTransformProperty [0].m_number_value;
						scale.y = scalePhysicsTransformProperty [1].m_number_value;
						scale.z = scalePhysicsTransformProperty [2].m_number_value;

						const auto& physicsModelShapeProperty = physicsComponentProperties->second.m_object_value.find("model_type")->second.m_string_value;
						JPH::RefConst<JPH::Shape> modelShape;
						if (physicsModelShapeProperty == "CUBE")
						{
							physicsComponent->SetModelType(ModelType::CUBE);
							modelObject->SetModelType(ModelType::CUBE);
						}
						else if (physicsModelShapeProperty == "SPHERE")
						{
							physicsComponent->SetModelType(ModelType::SPHERE);
							modelObject->SetModelType(ModelType::SPHERE);
						}
						else if (physicsModelShapeProperty == "CAPSULE")
						{
							physicsComponent->SetModelType(ModelType::CAPSULE);
							modelObject->SetModelType(ModelType::CAPSULE);
						}
						else if (physicsModelShapeProperty == "CYLINDER")
						{
							physicsComponent->SetModelType(ModelType::CYLINDER);
							modelObject->SetModelType(ModelType::CYLINDER);
						}
						else if (physicsModelShapeProperty == "PLANE")
						{
							physicsComponent->SetModelType(ModelType::PLANE);
							modelObject->SetModelType(ModelType::PLANE);
						}
						else if (physicsModelShapeProperty == "QUAD")
						{
							physicsComponent->SetModelType(ModelType::QUAD);
							modelObject->SetModelType(ModelType::QUAD);
						}
						else if (physicsModelShapeProperty == "CUSTOM_CUBE")
						{
							physicsComponent->SetModelType(ModelType::CUSTOM_CUBE);
							modelObject->SetModelType(ModelType::CUSTOM_CUBE);
						}
						else if (physicsModelShapeProperty == "CUSTOM_GIANT_FLOOR")
						{
							physicsComponent->SetModelType(ModelType::CUSTOM_GIANT_FLOOR);
							modelObject->SetModelType(ModelType::CUSTOM_GIANT_FLOOR);
						}
						else if (physicsModelShapeProperty == "CUSTOM_GIANT_WALL")
						{
							physicsComponent->SetModelType(ModelType::CUSTOM_GIANT_WALL);
							modelObject->SetModelType(ModelType::CUSTOM_GIANT_WALL);
						}
						else if (physicsModelShapeProperty == "CUSTOM_WALL")
						{
							physicsComponent->SetModelType(ModelType::CUSTOM_WALL);
							modelObject->SetModelType(ModelType::CUSTOM_WALL);
						}

						const auto& physicsMotionTypeProperty = physicsComponentProperties->second.m_object_value.find("motion_type")->second.m_string_value;
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

						const auto& physicsActivationProperty = physicsComponentProperties->second.m_object_value.find("activation")->second.m_string_value;
						JPH::EActivation activation = JPH::EActivation::DontActivate;
						if (physicsActivationProperty == "DontActivate")
						{
							activation = JPH::EActivation::DontActivate;
						}
						else if (physicsActivationProperty == "Activate")
						{
							activation = JPH::EActivation::Activate;
						}

						vec3f linearVelocity(0.0f, 0.0f, 0.0f);
						vec3f angularVelocity(0.0f, 0.0f, 0.0f);

						const auto& physicsVelocityProperty = physicsComponentProperties->second.m_object_value.find("velocity");

						const auto& linearVelocityPhysicsVelocityProperty = physicsVelocityProperty->second.m_object_value.find("linear_velocity")->second.m_array_value;
						linearVelocity.x = linearVelocityPhysicsVelocityProperty [0].m_number_value;
						linearVelocity.y = linearVelocityPhysicsVelocityProperty [1].m_number_value;
						linearVelocity.z = linearVelocityPhysicsVelocityProperty [2].m_number_value;

						const auto& angularVelocityPhysicsVelocityProperty = physicsVelocityProperty->second.m_object_value.find("angular_velocity")->second.m_array_value;
						angularVelocity.x = angularVelocityPhysicsVelocityProperty [0].m_number_value;
						angularVelocity.y = angularVelocityPhysicsVelocityProperty [1].m_number_value;
						angularVelocity.z = angularVelocityPhysicsVelocityProperty [2].m_number_value;

						const auto& physicsGravityFactorProperty = physicsComponentProperties->second.m_object_value.find("gravity_factor");
						float32 gravityFactor = physicsGravityFactorProperty->second.m_number_value;

						const auto& physicsRestitutionProperty = physicsComponentProperties->second.m_object_value.find("restitution");
						float32 restitution = physicsRestitutionProperty->second.m_number_value;

						const auto& physicsFrictionProperty = physicsComponentProperties->second.m_object_value.find("friction");
						float32 friction = physicsFrictionProperty->second.m_number_value;

						// Audio component
						const auto& audioComponentValue = componentValue.find("audio");
						const auto& audioComponentProperties = audioComponentValue->second.m_object_value.find("properties");


						const auto& modelsValue = objectValue.m_object_value.find("models")->second.m_object_value;
						const auto& modelvalue = modelsValue.find("model")->second.m_object_value;
						const auto& modelIdentifier = modelvalue.find("identifier")->second.m_string_value;
						const auto& modelPath = modelvalue.find("path")->second.m_string_value;
						Model* model = new Model(modelPath);
						modelObject->AddModel(model);
						scene->AddObject(object);
						physicsComponent->GetBody()->GetMotionProperties()->SetLinearVelocity(JPHVec3(linearVelocity));
						physicsComponent->GetBody()->GetMotionProperties()->SetAngularVelocity(JPHVec3(angularVelocity));
						physicsComponent->GetBody()->GetMotionProperties()->SetGravityFactor(gravityFactor);
						physicsComponent->GetBody()->SetRestitution(restitution);
						physicsComponent->GetBody()->SetFriction(friction);
						physicsComponent->GetBodyInterface()->SetMotionType(physicsComponent->GetBody()->GetID(), motionType, activation);
					}
					else
					{
						scene->AddObject(object);
					}
					//object->AddObserver(scene);
				}
				m_scenes.push_back(scene);
			}
		}
		catch (const std::exception& e)
		{
			std::cout << "Error: " << e.what() << std::endl;
		}
		return 0;
	}

	void Serializer::SetPhysicSystem(PhysicSystem* p_physic_system)
	{
		m_physic_system = p_physic_system;
	}

	void Serializer::SetScenes(std::vector<Scene*> p_scenes)
	{
		m_scenes = p_scenes;
	}

	std::vector<Scene*> Serializer::GetScenes()
	{
		return m_scenes;
	}

	void printJsonValue(const JsonValue& jsonValue, int depth)
	{
		switch (jsonValue.m_type)
		{
			case JsonType::Object:
				std::cout << "{\n";
				for (const auto& pair : jsonValue.m_object_value)
				{
					std::cout << std::string(depth + 1, '\t') << "\"" << pair.first << "\": ";
					printJsonValue(pair.second, depth + 1);
					std::cout << ",\n";
				}
				std::cout << std::string(depth, '\t') << "}";
				break;
			case JsonType::Array:
				std::cout << "[\n";
				for (const auto& value : jsonValue.m_array_value)
				{
					std::cout << std::string(depth + 1, '\t');
					printJsonValue(value, depth + 1);
					std::cout << ",\n";
				}
				std::cout << std::string(depth, '\t') << "]";
				break;
			case JsonType::String:
				std::cout << "\"" << jsonValue.m_string_value << "\"";
				break;
			case JsonType::Number:
				std::cout << jsonValue.m_number_value;
				break;
			case JsonType::True:
				std::cout << "true";
				break;
			case JsonType::False:
				std::cout << "false";
				break;
			case JsonType::Null:
				std::cout << "null";
				break;
		}
	}
}