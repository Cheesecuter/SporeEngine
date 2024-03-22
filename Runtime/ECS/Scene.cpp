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

	void Scene::AddObject(std::shared_ptr<Object> object)
	{
		objectMapper.insert(std::make_pair(object->identifier, object));
	}

	void Scene::DeleteObject(std::shared_ptr<Object> object)
	{
		std::map<std::string, std::shared_ptr<Object>>::iterator it = objectMapper.find(object->identifier);
		if (it != objectMapper.end())
		{
			objectMapper.erase(it);
		}
	}

	void Scene::DeleteObject(std::string identifier_p)
	{
		std::map<std::string, std::shared_ptr<Object>>::iterator it = objectMapper.find(identifier_p);
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

	void Scene::Render(std::vector<Shader> shaders_p, Camera* camera_p,
					   uint32 scrWidth_p, uint32 scrHeight_p,
					   mat4f projection_p, mat4f view_p, mat4f model_p)
	{
		for (const std::pair<std::string, std::shared_ptr<Object>> it : objectMapper)
		{
			std::shared_ptr<Object> object = it.second;
			if (!object->modelMapper.empty())
			{
				object->Render(shaders_p, camera_p, scrWidth_p, scrHeight_p,
							   projection_p, view_p, model_p);
			}
		}
	}
}
