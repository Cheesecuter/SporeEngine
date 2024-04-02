#include <Scene.hpp>

namespace Spore
{
	Scene::Scene(std::string p_identifier)
	{
		m_identifier = p_identifier;
	}

	Scene::~Scene()
	{

	}

	void Scene::AddObject(Object* p_object)
	{
		m_object_mapper.insert(std::make_pair(p_object->m_identifier, p_object));
		p_object->AddObserver(this);
	}

	void Scene::DeleteObject(Object* p_object)
	{
		std::map<std::string, Object*>::iterator it = m_object_mapper.find(p_object->m_identifier);
		if (it != m_object_mapper.end())
		{
			m_object_mapper.erase(it);
		}
	}

	void Scene::DeleteObject(std::string p_identifier)
	{
		std::map<std::string, Object*>::iterator it = m_object_mapper.find(p_identifier);
		if (it != m_object_mapper.end())
		{
			m_object_mapper.erase(it);
		}
	}

	void Scene::OnObjectDeleted(Object* p_object)
	{
		m_object_mapper.erase(p_object->m_identifier);
	}

	void Scene::Update(float32 p_deltaTime)
	{

	}

	void Scene::Render(std::vector<Shader*> p_shaders, Camera* p_camera,
					   uint32 p_screen_width, uint32 p_screen_height,
					   mat4f p_projection, mat4f p_view, mat4f p_model)
	{
		for (const std::pair<std::string, Object*> it : m_object_mapper)
		{
			Object* object = it.second;
			if (object->m_type == "default")
			{
				/*if (!object->modelMapper.empty())
				{
					object->Render(shaders_p, camera_p, scrWidth_p, scrHeight_p,
								   projection_p, view_p, model_p);
				}*/
			}
			else if (object->m_type == "model")
			{
				ModelObject* modelObject = dynamic_cast<ModelObject*>(object);
				if (!modelObject->m_model_mapper.empty())
				{
					modelObject->Render(p_shaders, p_camera, p_screen_width, p_screen_height,
								   p_projection, p_view, p_model);
				}
			}
			else if (object->m_type == "plane")
			{
				Plane* plane = dynamic_cast<Plane*>(object);
				Texture* floorTexture = AssetsManager::GetInstance().m_texture_mapper.find("default.png")->second;
				plane->Render(p_shaders, floorTexture, p_model);
			}
			else if (object->m_type == "light")
			{
				Light* light = dynamic_cast<Light*>(object);
				light->Render(p_shaders, p_camera, p_screen_width, p_screen_height,
							  p_projection, p_view, p_model);
			}
		}
	}
}
