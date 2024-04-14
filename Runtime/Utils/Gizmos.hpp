#pragma once

#include <Types.hpp>
#include <IMGUI_GLFW_OPENGL3.hpp>
#include <Window.hpp>

#include <ImGuizmo/ImGuizmo.h>


namespace Spore
{
	class Gizmos
	{
	public:
		Gizmos();
		virtual ~Gizmos();
		void EditTransform(MainWindow* p_window, 
						   float32* p_camera_view, float32* p_camera_projection,
						   float32* p_matrix, bool p_edit_transform_decomposition);
		vec3f GetPosition();
		vec3f GetRotation();
		vec3f GetScale();

	protected:

	private:
		static ImGuizmo::OPERATION m_current_gizmo_operation;
		int m_gizmo_count;
		vec3f m_position;
		vec3f m_rotation;
		vec3f m_scale;
	};
}