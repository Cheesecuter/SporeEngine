#pragma once

#include <Types.hpp>
#include <Model.hpp>
#include <Shader.hpp>
#include <Camera.hpp>
#include <AssetsManager.hpp>
#include <Component.hpp>
#include <TransformComponent.hpp>
#include <ShaderComponent.hpp>
#include <ModelObserver.hpp>
#include <ObjectObserver.hpp>

namespace Spore
{
	class Object : public ModelObserver
	{
	public:
		Object(const std::string& p_identifier, const bool p_light = false);
		virtual ~Object();

		std::string m_identifier;
		std::string m_type = "default";
		bool m_selected = false;
		void AddObserver(ObjectObserver* p_observer);
		void RemoveObserver(ObjectObserver* p_observer);
		void DeleteObject();
		void Update(float32 p_deltaTime);
		virtual void Render(std::vector<Shader*> p_shaders, Camera* p_camera,
					uint32 p_screen_width, uint32 p_screen_height,
					mat4f p_projection, mat4f p_view, mat4f p_model);

		bool AddComponent(Component* p_component);
		bool HasComponent(const std::string& p_component_name) const;
		std::unordered_map<std::string, Component*> GetComponents();
		Component* GetComponent(const std::string& p_component_name);
		template<typename TComponent>
		TComponent* TryGetComponent(const std::string& p_component_name);

		void SetPosition(const vec3f& p_position);
		void SetRotation(const vec3f& p_rotation);
		void SetScale(const vec3f& p_scale);
		vec3f GetPosition() const;
		vec3f GetRotation() const;
		vec3f GetScale() const;
		vec3f GetFront() const;
		vec3f GetRight() const;
		vec3f GetUp() const;

	protected:
		std::unordered_map<std::string, Component*> m_components;
		Shader* m_model_shader;

	private:
		std::vector<ObjectObserver*> m_observer_list;
	};
}
