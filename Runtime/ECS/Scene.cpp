#include <Scene.hpp>

namespace Spore
{
	Scene::Scene(std::string identifier_p)
	{
		identifier = identifier_p;
	}

	Scene::~Scene()
	{

	}

	void Scene::AddObject(Object* object_p)
	{
		objectMapper.insert(std::make_pair(object_p->identifier, object_p));
		object_p->AddObserver(this);
	}

	void Scene::DeleteObject(Object* object_p)
	{
		std::map<std::string, Object*>::iterator it = objectMapper.find(object_p->identifier);
		if (it != objectMapper.end())
		{
			objectMapper.erase(it);
		}
	}

	void Scene::DeleteObject(std::string identifier_p)
	{
		std::map<std::string, Object*>::iterator it = objectMapper.find(identifier_p);
		if (it != objectMapper.end())
		{
			objectMapper.erase(it);
		}
	}

	void Scene::OnObjectDeleted(Object* object_p)
	{
		objectMapper.erase(object_p->identifier);
	}

	void Scene::Update(float32 deltaTime)
	{

	}

	void Scene::Render(std::vector<Shader*> shaders_p, Camera* camera_p,
					   uint32 scrWidth_p, uint32 scrHeight_p,
					   mat4f projection_p, mat4f view_p, mat4f model_p)
	{
		for (const std::pair<std::string, Object*> it : objectMapper)
		{
			Object* object = it.second;
			if (object->type == "default")
			{
				/*if (!object->modelMapper.empty())
				{
					object->Render(shaders_p, camera_p, scrWidth_p, scrHeight_p,
								   projection_p, view_p, model_p);
				}*/
			}
			else if (object->type == "model")
			{
				ModelObject* modelObject = dynamic_cast<ModelObject*>(object);
				if (!modelObject->modelMapper.empty())
				{
					modelObject->Render(shaders_p, camera_p, scrWidth_p, scrHeight_p,
								   projection_p, view_p, model_p);
				}
			}
			else if (object->type == "plane")
			{
				Plane* plane = dynamic_cast<Plane*>(object);
				Texture* floorTexture = AssetsManager::GetInstance().textureMapper.find("default.png")->second;
				plane->Render(shaders_p, floorTexture, model_p);
			}
			else if (object->type == "light")
			{
				Light* light = dynamic_cast<Light*>(object);
				light->Render(shaders_p, camera_p, scrWidth_p, scrHeight_p,
							  projection_p, view_p, model_p);
			}
		}
	}
}
