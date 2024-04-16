#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>

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

using namespace Spore;

class JsonParserTest
{
public:
	
	std::vector<Scene*> scenes;

	int runtest(PhysicSystem* p_physic_system);
};