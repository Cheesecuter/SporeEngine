#include <Gizmos.hpp>
#include <Keyboard.hpp>

namespace Spore
{
	ImGuizmo::OPERATION Gizmos::m_current_gizmo_operation;

	Gizmos::Gizmos()
	{
		m_current_gizmo_operation = ImGuizmo::TRANSLATE;
		m_gizmo_count = 1;
	}

	Gizmos::~Gizmos()
	{

	}

	void Gizmos::EditTransform(MainWindow* p_window, 
							   float32* p_camera_view, float32* p_camera_projection,
							   float32* p_matrix, bool p_edit_transform_decomposition)
	{
		static ImGuizmo::MODE currentGizmoMode(ImGuizmo::WORLD);
		static bool useSnap = false;
		static float snap [3] = { 1.0f, 1.0f, 1.0f };
		static float bounds [] = { -0.5f, -0.5f, -0.5f, 0.5f, 0.5f, 0.5f };
		static float boundsSnap [] = { 0.1f, 0.1f, 0.1f };
		static bool boundSizing = false;
		static bool boundSizingSnap = false;

		if (p_edit_transform_decomposition)
		{
			if (Keyboard::GetInstance().GetKey(p_window) == KEY_R)
			{
				m_current_gizmo_operation = ImGuizmo::TRANSLATE;
			}
			if (Keyboard::GetInstance().GetKey(p_window) == KEY_T)
			{
				m_current_gizmo_operation = ImGuizmo::ROTATE;
			}
			if (Keyboard::GetInstance().GetKey(p_window) == KEY_Y)
			{
				m_current_gizmo_operation = ImGuizmo::SCALE;
			}
		}

		vec2f scenePos = p_window->GetRenderPipeline()->GetScenePos();
		vec2f sceneSize = p_window->GetRenderPipeline()->GetSceneSize();
		ImGuizmo::SetRect(scenePos.x, 0.0f, sceneSize.x, sceneSize.y);

		float deltaMatrix = 0.1f;
		ImGuizmo::Manipulate(p_camera_view, p_camera_projection, m_current_gizmo_operation, currentGizmoMode, p_matrix, NULL, useSnap ? &snap [0] : NULL, boundSizing ? bounds : NULL, boundSizingSnap ? boundsSnap : NULL);

		if (ImGuizmo::IsUsing())
		{
			ImGuizmo::Manipulate(p_camera_view, p_camera_projection, m_current_gizmo_operation, currentGizmoMode, p_matrix, NULL, useSnap ? &snap [0] : NULL, boundSizing ? bounds : NULL, boundSizingSnap ? boundsSnap : NULL);

		}

		//ImGuizmo::ViewManipulate(p_camera_view, 1.0f, ImVec2(scenePos.x, 0.0f), ImVec2(128, 128), 0x10101010);
		ImGuizmo::DecomposeMatrixToComponents(p_matrix, glm::value_ptr(m_position), glm::value_ptr(m_rotation), glm::value_ptr(m_scale));
		ImGuizmo::RecomposeMatrixFromComponents(glm::value_ptr(m_position), glm::value_ptr(m_rotation), glm::value_ptr(m_scale), p_matrix);
	}

	vec3f Gizmos::GetPosition()
	{
		return m_position;
	}

	vec3f Gizmos::GetRotation()
	{
		return m_rotation;
	}

	vec3f Gizmos::GetScale()
	{
		return m_scale;
	}
}