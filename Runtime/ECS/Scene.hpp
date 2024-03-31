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
		Scene(std::string identifier_p);
		~Scene();

		std::string identifier;
		std::map<std::string, std::shared_ptr<Object>> objectMapper;
		vec4f enviromentColor = vec4f(0.725f, 0.725f, 0.725f, 1.0f);

		void AddObject(std::shared_ptr<Object> object_p);
		void DeleteObject(std::shared_ptr<Object> object_p);
		void DeleteObject(std::string identifier_p);
		void OnObjectDeleted(Object* object_p) override;
		void Update(float32 deltaTime);
		void Render(std::vector<Shader*> shaders_p, Camera* camera_p,
					uint32 scrWidth_p, uint32 scrHeight_p,
					mat4f projection_p, mat4f view_p, mat4f model_p);

	private:
	};
}

#endif
