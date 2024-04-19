#pragma once

#include <Types.hpp>
#include <IMGUI_GLFW_OPENGL3.hpp>
#include <Window.hpp>
#include <Files.hpp>
#include <AssetsManager.hpp>
#include <FileExplorer.hpp>
#include <Shader.hpp>
#include <Texture.hpp>
#include <Model.hpp>
#include <Audio.hpp>
#include <Scene.hpp>
#include <Gizmos.hpp>
#include <Serializer.hpp>

#include <Windows.h>

namespace Spore
{
	class UIProxy
	{
	public:

	};

	class UI
	{
	public:
		UI(MainWindow* p_window);
		~UI();
		void InitImGui(MainWindow* p_window);
		void Init();
		void Terminate();
		void NewFrame();
		void Render();
		void RenderPanels(MainWindow* p_window);
		void ShowDemoWindow();
		float32 m_delta_time = 0.0f;

	protected:

	private:
		bool m_show_console = false;
		bool m_show_demo_window = false;
		bool m_show_another_window = false;
		bool m_show_scene_panel = false;
		Gizmos* m_gizmos;
		std::filesystem::path m_import_assets_path = Files::GetInstance().GetAssetsPath();
		MainWindow* m_window;
		std::string m_selected_scene_identifier = "";
		Scene* m_selected_scene;
		std::string m_selected_object_identifier = "";
		Object* m_selected_object;
		std::unordered_map<std::string, PostProcess*> m_post_process_mapper;
		Texture* m_button_image_reset;

		void InitImages();
		void RenderMenuBar(MainWindow* p_window);
		void RenderHierarchyPanel(MainWindow* p_window);
		void RenderScenePanel(MainWindow* p_window);
		void RenderInspectorPanel(MainWindow* p_window);
		void RenderProjectPanel(MainWindow* p_window);
		void RenderConsolePanel(MainWindow* p_window);
		void RenderGizmos(MainWindow* p_window);
	};
}
