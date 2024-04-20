#include <BasicModelsRegister.hpp>

namespace Spore
{
	BasicModelsRegister::BasicModelsRegister()
	{
		Model* cubeModel = new Model("./Assets/Models/_basic models/cube.fbx");
		Model* sphereModel = new Model("./Assets/Models/_basic models/sphere.fbx");
		Model* capsuleModel = new Model("./Assets/Models/_basic models/capsule.fbx");
		Model* cylinderModel = new Model("./Assets/Models/_basic models/cylinder.fbx");
		Model* planeModel = new Model("./Assets/Models/_basic models/plane.fbx");
		Model* quadModel = new Model("./Assets/Models/_basic models/plane.fbx");
	}

	BasicModelsRegister::~BasicModelsRegister()
	{

	}
}