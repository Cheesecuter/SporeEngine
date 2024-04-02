#pragma once
#ifndef SCENE_HPP
#define SCENE_HPP

#include <Types.hpp>
#include <Object.hpp>
#include <ModelObject.hpp>
#include <Light.hpp>
#include <Plane.hpp>

namespace Spore
{
	class Scene : public ObjectObserver
	{
	public:
		Scene(std::string p_identifier);
		~Scene();

		std::string m_identifier;
		std::map<std::string, Object*> m_object_mapper;
		vec4f m_enviroment_color = vec4f(0.725f, 0.725f, 0.725f, 1.0f);
		int m_object_index = 0;

		void AddObject(Object* p_object);
		void DeleteObject(Object* p_object);
		void DeleteObject(std::string p_identifier);
		void OnObjectDeleted(Object* p_object) override;
		void Update(float32 p_deltaTime);
		void Render(std::vector<Shader*> p_shaders, Camera* p_camera,
					uint32 p_screen_width, uint32 p_screen_height,
					mat4f p_projection, mat4f p_view, mat4f p_model);

	private:
	};
}

#endif
