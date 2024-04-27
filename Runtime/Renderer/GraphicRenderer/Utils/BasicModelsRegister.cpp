#include <BasicModelsRegister.hpp>
#include <Model.hpp>

namespace Spore
{
	BasicModelsRegister::BasicModelsRegister()
	{
		Model* cubeModel		= new Model("./Assets/Utils/Models/cube.obj");
		Model* sphereModel		= new Model("./Assets/Utils/Models/sphere.obj");
		Model* capsuleModel		= new Model("./Assets/Utils/Models/capsule.obj");
		Model* cylinderModel	= new Model("./Assets/Utils/Models/cylinder.obj");
		Model* planeModel		= new Model("./Assets/Utils/Models/plane.obj");
		Model* quadModel		= new Model("./Assets/Utils/Models/plane.obj");
	}

	BasicModelsRegister::~BasicModelsRegister()
	{

	}
}