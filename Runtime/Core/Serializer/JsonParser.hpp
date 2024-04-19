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
		JsonValue parse(const std::string& jsonStr);
		std::string toJsonString(JsonValue p_value) const;

	protected:

	private:
		int index;
		JsonValue parseValue(const std::string& jsonStr);
		JsonValue parseObject(const std::string& jsonStr);
		JsonValue parseArray(const std::string& jsonStr);
		JsonValue parseString(const std::string& jsonStr);
		JsonValue parseNumber(const std::string& jsonStr);
		void skipWhilespace(const std::string& jsonStr);
	};
}
