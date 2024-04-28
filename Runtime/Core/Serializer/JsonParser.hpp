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
		JsonValue Parse(const std::string& p_json_str);
		std::string ToJsonString(JsonValue p_value) const;

	protected:

	private:
		int index;
		JsonValue ParseValue(const std::string& p_json_str);
		JsonValue ParseObject(const std::string& p_json_str);
		JsonValue ParseArray(const std::string& p_json_str);
		JsonValue ParseString(const std::string& p_json_str);
		JsonValue ParseNumber(const std::string& p_json_str);
		void SkipWhilespace(const std::string& p_json_str);
	};
}
