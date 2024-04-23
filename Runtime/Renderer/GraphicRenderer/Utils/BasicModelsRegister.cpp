#include <BasicModelsRegister.hpp>

namespace Spore
{
	BasicModelsRegister::BasicModelsRegister()
	{
		Model* cubeModel = new Model("./Assets/Models/_basic models/cube.obj");
		Model* sphereModel = new Model("./Assets/Models/_basic models/sphere.obj");
		Model* capsuleModel = new Model("./Assets/Models/_basic models/capsule.obj");
		Model* cylinderModel = new Model("./Assets/Models/_basic models/cylinder.obj");
		Model* planeModel = new Model("./Assets/Models/_basic models/plane.obj");
		Model* quadModel = new Model("./Assets/Models/_basic models/plane.obj");
	}

	BasicModelsRegister::~BasicModelsRegister()
	{

	}
}