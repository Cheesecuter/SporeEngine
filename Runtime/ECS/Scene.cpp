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
		if (p_object->m_type == "model")
		{
			ModelObject* modelObject = dynamic_cast<ModelObject*>(p_object);
			PhysicsComponent* physicsComponent = dynamic_cast<PhysicsComponent*>(p_object->GetComponents().find("Physics")->second);

			JPH::RefConst<JPH::Shape> box_shape = new JPH::BoxShape(JPH::Vec3(1.0f, 1.0f, 1.0f));
			physicsComponent->SetBodyCreationSettings(box_shape, JPH::RVec3(0, 10, 0),
													  JPH::Quat::sIdentity(), JPH::EMotionType::Dynamic,
													  Layers::MOVING);
			physicsComponent->CreateAndAddBody(m_body_interface);
		}
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

	void Scene::SetPhysicsSystem(JPH::PhysicsSystem* p_physics_system)
	{
		m_physics_system = p_physics_system;
		m_body_interface = &p_physics_system->GetBodyInterface();
	}

	void Scene::SetJobSystem(JPH::JobSystem* p_job_system)
	{
		m_job_system = p_job_system;
	}

	void Scene::SetTempAllocator(JPH::TempAllocator* p_temp_allocator)
	{
		m_temp_allocator = p_temp_allocator;
	}

	void Scene::InitPhysics()
	{
		m_physics_system->SetBodyActivationListener(&m_body_activation_listener);
		CreateFloor();
	}

	JPH::BodyInterface* Scene::GetBodyInterface()
	{
		return m_body_interface;
	}

	JPH::ContactListener* Scene::GetContactListener()
	{
		return nullptr;
	}

	bool Scene::IsActive(uint32 p_step)
	{
		bool flag = false;
		for (const std::pair<std::string, Object*> it : m_object_mapper)
		{
			Object* object = it.second;
			if (object->m_type == "model")
			{
				ModelObject* modelObject = dynamic_cast<ModelObject*>(object);
				if(modelObject.)
			}
		}
	}

	JPH::Body& Scene::CreateFloor(float32 p_size)
	{
		const float scale = 1.0f;

		JPH::Body& floor = *m_body_interface->CreateBody(
			JPH::BodyCreationSettings(
				new JPH::BoxShape(scale * JPH::Vec3(0.5f * p_size, 1.0f, 0.5f * p_size), 0.0f),
				JPH::RVec3(scale * JPH::Vec3(0.0f, -1.0f, 0.0f)),
				JPH::Quat::sIdentity(), JPH::EMotionType::Static, Layers::NON_MOVING));
		m_body_interface->AddBody(floor.GetID(), JPH::EActivation::DontActivate);
		return floor;
	}
}
