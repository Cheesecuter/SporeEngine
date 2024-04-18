#pragma once

#include <Types.hpp>
#include <IMGUI_GLFW_OPENGL3.hpp>

namespace Spore
{
	class Object;

	class Component
	{
	public:
		Component() = default;
		virtual ~Component();

		bool IsDirty() const;
		void SetDirtyFlag(bool p_is_dirty);
		std::string GetName() const;
		void SetReferencedObject(Object* p_object);
		Object* GetReferencedObject();
		virtual void InspectorPanel();
		virtual void Tick(float32 p_delta_time);

	protected:
		std::string m_name = "";
		Object* m_referenced_object = nullptr;
		bool m_is_dirty { false };
		bool m_is_scale_dirty { false };

	private:

	};
}
