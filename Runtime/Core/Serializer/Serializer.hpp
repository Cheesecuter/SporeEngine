#pragma once

#include <PhysicSystem.hpp>
#include <JsonParser.hpp>

namespace Spore
{
	class Serializer
	{
	public:
		Serializer();
		virtual ~Serializer();
		int Serialize(const char* p_path);
		int Deserialize(const char* p_path);
		void SetPhysicSystem(PhysicSystem* p_physic_system);
		void SetScenes(std::vector<Scene*> p_scenes);
		std::vector<Scene*> GetScenes();

	protected:

	private:
		PhysicSystem* m_physic_system = nullptr;
		JsonValue m_json_value;
		std::vector<Scene*> m_scenes;
	};
}