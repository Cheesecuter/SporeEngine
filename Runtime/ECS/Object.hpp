#pragma once
#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <Types.hpp>
#include <Model.hpp>
#include <Shader.hpp>
#include <Camera.hpp>
#include <AssetsManager.hpp>
#include <Component.hpp>
#include <TransformComponent.hpp>
#include <ShaderComponent.hpp>

namespace Spore
{
	class Object;

	class ObjectObserver
	{
	public:
		virtual ~ObjectObserver()
		{
		}
		virtual void OnObjectDeleted(Object* object_p) = 0;
	};

	class Object : public ModelObserver, std::enable_shared_from_this<Object>
	{
	public:
		Object(const std::string& identifier_p, const bool light_p = false);
		virtual ~Object();

		std::string identifier;
		std::map<std::string, Model*> modelMapper;
		uint32 VAO, VBO, EBO;
		bool selected = false;

		void AddModel(Model* model_p);
		void DeleteModel(Model model_p);
		void DeleteModel(std::string identifier_p);
		void OnModelDeleted(Model* model) override;
		void AddObserver(std::shared_ptr<ObjectObserver> observer_p);
		void RemoveObserver(std::shared_ptr<ObjectObserver> observer_p);
		void DeleteObject();
		void Update(float32 deltaTime);
		virtual void Render(std::vector<Shader*> shaders_p, Camera* camera_p,
					uint32 scrWidth_p, uint32 scrHeight_p,
					mat4f projection_p, mat4f view_p, mat4f model_p);

		bool HasComponent(const std::string& componentName_p) const;
		std::unordered_map<std::string, Component*> GetComponents();
		template<typename TComponent>
		TComponent* TryGetComponent(const std::string& componentName_p);
		template<typename TComponent>
		const TComponent* TryGetComponentConst(const std::string& componentName) const;

		void SetPosition(const vec3f& position_p);
		void SetRotation(const vec3f& rotation_p);
		void SetScale(const vec3f& scale_p);
		vec3f GetPosition() const;
		vec3f GetRotation() const;
		vec3f GetScale() const;
		vec3f GetFront() const;
		vec3f GetRight() const;
		vec3f GetUp() const;

	protected:
		std::unordered_map<std::string, Component*> components;
		Shader* modelShader;

	private:
		std::vector<std::shared_ptr<ObjectObserver>> observerList;
	};
}

#endif
